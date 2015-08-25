#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "zordinate.h"

void runit(char *input);

int main () {
  runit("A");
  runit("AB");
  runit("ABC");
  runit("ABCD");
  runit("ABCDEFGHIJKLMNOP");
  return 0;
}

void runit(char *input) {
  int i,j,len,wid;
  len = strlen(input);
  char *output = calloc(len, sizeof(unsigned char));
  wid = ceil(sqrt(len))*ceil(sqrt(len));
  lin2zord(input, output, len, wid);
  for(i=0;i<len/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ",(char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  wid = wid/2;
  lin2zord(input, output, len, wid);
  for(i=0;i<len/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ",(char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  free(output);
}

