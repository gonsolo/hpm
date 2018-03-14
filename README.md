# HPM
Floating point ascii image format

HPM makes it easy to manually to edit floating point images just like ascii ppm
images do.

The basic format is:

HPM7
# This is a comment
3 2
0.0 0.0 0.0	0.0 0.0 0.0	0.0 0.0 0.0
0.0 0.0 0.0	0.0 0.0 0.0	0.0 0.0 0.0

where HPM7 is the magic number,
hashmarks introduce comments,
3 and 2 are the width and the height of the image,
followed by width times height times 3 RGB values
in floating point format.

Converters to and from 32 bit floating point TIFF images are provided.

