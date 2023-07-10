#include <stdio.h>
#include <stdlib.h>
#include <libraw/libraw.h>

void err(const char * msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

void usage()
{
	printf("\nUsage: $ hotpixels filename [threshold]\n");
	printf("\tthreshold default: 15000\n");
	exit(0);
}

int main(int argc, char **argv)
{
	unsigned short threshold = 15000;

	if (argc < 2)
		usage();

	if (argc >= 3)
		threshold = atoi(argv[2]);


	LibRaw RawProcessor;

	if (RawProcessor.open_file(argv[1]) != LIBRAW_SUCCESS) 
		err("Raw file open failed...\n"); 

	if (RawProcessor.unpack() != LIBRAW_SUCCESS)
		err("Raw data unpack failed...\n"); 

	if (!RawProcessor.imgdata.rawdata.raw_image) 
		err("no raw data.\n");

	printf("hotpixel assessment, threshold = %d\n", threshold);

	int width = RawProcessor.imgdata.sizes.raw_width;
	int height = RawProcessor.imgdata.sizes.raw_height;
	unsigned short * rawimage = RawProcessor.imgdata.rawdata.raw_image;
	printf("raw image dimensions: %dx%d\n",width,height);
	unsigned hotcount = 0;
	unsigned maxval = 0;

	for (unsigned r = 0; r < height; r++) {
		for (unsigned c = 0; c < width; c++) {
			unsigned pos = r*width + c;
			if (rawimage[pos] > maxval) maxval = rawimage[pos];
			if (rawimage[pos] >= threshold) {
				printf("%d,%d: %c\n",r,c, RawProcessor.imgdata.idata.cdesc[RawProcessor.COLOR(r,c)]);
				hotcount++;
			}
		}
	}

	printf("hot pixel count: %d, maxval: %d\n", hotcount, maxval);

	RawProcessor.recycle();	
}