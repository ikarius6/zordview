#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "zordinate.h"

void runit(char *input);

int main () {
  runit("ABCDEFGHI");
  return 0;
}

void runit(char *input) {
  int i,j,len,wid, outlen;
  len = strlen(input);
  // The first power of two greater than sqrt(len)
  wid = pow(2, ceil(log2(sqrt(len))));
  printf("wid %d\n",wid);
  outlen = pow(2, ceil(log2(len/(float)wid)))*wid;
  char *output = calloc(outlen, sizeof(unsigned char));
  lin2zord(input, output, len, wid);
  for(i=0;i<outlen/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (char)*(output+i*wid+j) ? (char)*(output+i*wid+j) : ' ');
    }
    printf("|\n");
  }
  free(output);
  wid = wid/2;
  outlen = pow(2, ceil(log2(len/(float)wid)))*wid;
  output = calloc(outlen, sizeof(unsigned char));
  printf("wid %d\n",wid);
  lin2zord(input, output, len, wid);
  for(i=0;i<outlen/wid;i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (char)*(output+i*wid+j) ? (char)*(output+i*wid+j) : ' ');
    }
    printf("|\n");
  }
  free(output);
}

