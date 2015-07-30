/* Based on LibPNG example A.Greensted
 * http://www.labbookpages.co.uk
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

long readInfile(char *filename, char **buffer);
float *zordCreateImage(char *linarray, long len);

// This takes the float value 'val', converts it to red, green & blue values, then 
// sets those values into the image memory buffer location pointed to by 'ptr'
inline void setRGB(png_byte *ptr, float val);

// This function actually writes out the PNG image file. The string 'title' is
// also written into the image file
int writeImage(char* filename, int width, int height, float *buffer, char* title);


int main(int argc, char *argv[])
{
	// Make sure that the output filename argument has been provided
	if (argc != 3) {
		fprintf(stderr, "Usage: ./zordview infile outfile.png\n");
		return 1;
	}

        char *linarray;
        long len = readInfile(argv[0], &linarray);
        if (len == 0) {
                return 1;
        }

	// Specify an output image size
	int width = (int)sqrt(powl(4, ceill(log2l(len)/2)));
	int height = (int)width;

	// The output is a 1D array of floats, length: width * height
	printf("Creating Image\n");
	float *buffer = zordCreateImage(linarray, len);
	if (buffer == NULL) {
		return 1;
	}

	// Save the image to a PNG file
	// The 'title' string is stored as part of the PNG file
	printf("Saving PNG\n");
	int result = writeImage(argv[2], width, height, buffer, "This is my test image");

	// Free up the memory used to store the image
        free(linarray);
	free(buffer);

	return result;
}

inline void setRGB(png_byte *ptr, float val)
{
	int v = (int)(val * 767);
	if (v < 0) v = 0;
	if (v > 767) v = 767;
	int offset = v % 256;

	if (v<256) {
		ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
	}
	else if (v<512) {
		ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
	}
	else {
		ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
	}
}

int writeImage(char* filename, int width, int height, float *buffer, char* title)
{
	int code = 0;
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	
	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			setRGB(&(row[x*3]), buffer[y*width + x]);
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}

long readInfile(char *filename, char **buffer)
{
        FILE *f = fopen(filename, "rb");
        if (!f) return 0;
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        printf("size %lx\n", fsize);
        fseek(f, 0, SEEK_SET);

        *buffer = malloc(fsize);
        fread(buffer, fsize, 1, f);
        fclose(f);

        return fsize;
}

float *zordCreateImage(char *linarray, long len)
{
        int i;
        long newlen = powl(4, ceill(log2l(len)/2));
        char *newbuf = calloc(newlen, sizeof(char));
        newbuf = memcpy(newbuf, linarray, len);
        // Now newbuf is square and zeroed after actual content
        char *zordarray = calloc(newlen, sizeof(char));
        lin2zord(newbuf, zordarray, newlen, sqrt(newlen));
        float *buffer = calloc(newlen, sizeof(float));
        for (i=0; i<newlen; i++)
        {
                buffer[i] = zordarray[i]/256;
        }
        free(zordarray);
        free(newbuf);
        return buffer;
}
