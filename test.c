#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "zordinate.h"

void runit(char *input);

int main () {
  runit("ABCDE");
  return 0;
}

void runit(char *input) {
  int i,j,len,wid;
  len = strlen(input);
  // The first power of two greater than sqrt(len)
  wid = pow(2, ceil(log2(sqrt(len))));
  printf("wid %d\n",wid);
  char *output = calloc(ceil(len/(float)wid)*wid, sizeof(unsigned char));
  lin2zord(input, output, len, wid);
  for(i=0;i<ceil(len/(float)wid);i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  free(output);
  wid = wid/2;
  output = calloc(ceil(len/(float)wid)*wid, sizeof(unsigned char));
  printf("wid %d\n",wid);
  lin2zord(input, output, len, wid);
  for(i=0;i<ceil(len/(float)wid);i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (char)*(output+i*wid+j));
    }
    printf("|\n");
  }
  free(output);
}

