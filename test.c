#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "zordinate.h"

int main () {
  unsigned char *input = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01"\
                         "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01";
  unsigned char *output;
  int i,j,len,wid;
  len = strlen(input);
  output = calloc(len, sizeof(unsigned char));
  //wid = sqrt(len);
  wid = 8;
  if (lin2zord(input, output, len, wid))
  {
    printf("bailing\n");
    return -1;
  }
  for(i=0;i<len/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ",(char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  wid = 16;
  if (lin2zord(input, output, len, wid))
  {
    printf("bailing\n");
    return -1;
  }
  for(i=0;i<len/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ",(char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  return 0;
}


