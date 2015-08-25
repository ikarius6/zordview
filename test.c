#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "zordinate.h"

void runit(char *input);

int main () {
  runit("ABC");
  return 0;
}

void runit(char *input) {
  int i,j,len,wid;
  len = strlen(input);
  char *output = calloc(len, sizeof(unsigned char));
  wid = ceil(sqrt(len));
  printf("wid %d\n",wid);
  lin2zord(input, output, len, wid);
  for(i=0;i<ceil(len/(float)wid);i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (i*wid+j)<len ? (char)*(output+i*wid+j) : ' ');
    }
    printf("|\n");
  }
  wid = wid/2;
  printf("wid %d\n",wid);
  lin2zord(input, output, len, wid);
  for(i=0;i<ceil(len/(float)wid);i++)
  {
    printf("| ");
    for(j=0;j<wid;j++)
    {
      printf("%c ", (i*wid+j)<len ? (char)*(output+i*wid+j) : ' ');
    }
    printf("|\n");
  }
  free(output);
}

