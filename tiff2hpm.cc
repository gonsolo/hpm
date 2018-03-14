#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include "tiffio.h"

void usage() {
	std::cout << "Usage: tiff2hpm <input> <output>" << std::endl;
	exit(EXIT_FAILURE);
}

void error(std::string message) {
	std::cerr << message << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	const char newline = '\n';

	if(argc != 3) usage();

	TIFF* tif = TIFFOpen(argv[1], "r");
	if(!tif) {
		error("Could not open tiff!");
	}

	std::ofstream out(argv[2]);
	if(!out) {
		error("Could not open output!");
	}
	uint16_t config;
	TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &config);
	if(config != PLANARCONFIG_CONTIG) {
		error("Only planar format is supported");
	}

	uint32_t height;
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

	uint32_t width;
	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);

	tsize_t scanlineSize = TIFFScanlineSize(tif);
	tdata_t buffer = _TIFFmalloc(scanlineSize);
	if(!buffer) {
		error("Could not allocate buffer!");
	}

	uint16_t channels;
	TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &channels);
	std::cout << "Channels: " << channels << newline;

	uint16_t format;
	TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &format);
	if (format != SAMPLEFORMAT_IEEEFP) {
		error("Sample format unknown!");
	}

	uint16_t samples;
	TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &samples);
	std::cout << "Samples: " << samples << newline;
	if(samples != 32) {
		error("Only 32 bit float images are supported!");
	}
	out << "HPM7" << newline;
	out << width << " " << height << newline;

	//float m = 0.f;
	//float mi = 0.f;

	for (int y = 0; y < height; ++y) {
		TIFFReadScanline(tif, buffer, y);
		for(int x = 0; x < width; ++x) {
			//for(int channel = 0; channel < channels; ++channel) {
			for(int channel = 0; channel < 3; ++channel) {
				float value = ((float*)buffer)[x*channels + channel];
				out << value<< newline;
				//m = std::max(m, value);
				//mi = std::min(mi, value);
			}
			for(int channel = 3; channel < channels; ++channel) {
				float value = ((float*)buffer)[x*channels + channel];
			}
		}
	}
	//std::cout << "Max: " << m << newline;
	//std::cout << "Min: " << mi << newline;

	//TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
	//TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	_TIFFfree(buffer);
	TIFFClose(tif);

	return EXIT_SUCCESS;
}

