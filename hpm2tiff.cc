#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include "tiffio.h"

void usage() {
	std::cout << "Usage: hpm2tiff <input> <output>" << std::endl;
	exit(EXIT_FAILURE);
}

void error(std::string message) {
	std::cerr << message << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	if(argc != 3) usage();
	std::ifstream input(argv[1]);
	if(!input) {
		error("Could not read input!");	
	}
	std::string magic;
	input >> magic;
	if(magic != "HPM7") {
		error("Not an HPM7 image!");
	}
	input >> std::ws;
	int c = input.peek();
	const int hashmark = '#';
	while(c == hashmark) {
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		c = input.peek();
	}
	input >> std::ws;
	int width, height;
	input >> width >> height;
	const int channels = 3;
	std::vector<float> image(channels*width*height);
	for(int h = 0; h < height; ++h) {
		for(int w = 0; w < width; ++w) {
			for(int c = 0; c < 3; ++c) {
				float value;
				input >> value;
				image[h*width*channels + w*channels + c] = value;
			}
		}
	}
	TIFF* tif = TIFFOpen(argv[2], "w");
	if(!tif) {
		error("Could not open tiff!");
	}

	TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
	TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
	TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 32);
	TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
	TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

	TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, channels);
	TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

	for(int h = 0; h < height; ++h) {
		float* buf = image.data() + h*width*channels;
		TIFFWriteScanline(tif, buf, h);
	}
	TIFFClose(tif);

	return EXIT_SUCCESS;
}

