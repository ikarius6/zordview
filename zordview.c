#include <stdio.h>
#include <png.h>

#define ERROR (-1)

static void user_error_fn(png_structp png_ptr, png_constant_charp msg)
{
  // Handle error here
}

void write_row_callback(png_ptr, png_uint_32 row, int pass)
{
  // stuff
}

int main(int argc, char *argv[])
{
  FILE *data_in_file;
  FILE *png_out_file;

  int length;
  char *data_in_file_name;
  char *png_out_file_name;
  
  png_byte *row_pointers[height];

  png_structp png_ptr;
  png_infop info_ptr;
  png_voidp user_error_ptr;

  length = strtoi(argv[1]);
  data_in_file_name = argv[2];
  png_out_file_name = argv[3];

  if (!(data_in_file = fopen(data_in_file_name, "r"))) return ERROR;



  if (!(png_out_file = fopen(png_out_file_name, "wb"))) return ERROR;
  if (!(png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
    (png_voidp)user_error_ptr, user_error_fn, NULL))) return ERROR;
  if (!(info_ptr = png_create_info_struct(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    return ERROR;
  }

  if (setjmp(png_jpmbuf(png_ptr)))
  {
    png_destroy_write_struct(&png_ptr, &infoptr);
    return (ERROR);
  }



  png_init_io(png_ptr, png_out_file);
  png_set_write_status_fn(png_ptr, write_row_callback);

  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, info_ptr);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_out_file);
  fclose(data_in_file);

  return 0;
}
