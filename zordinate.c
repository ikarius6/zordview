#include "zordinate.h"
#include <stdio.h>
#include <math.h>

int isPowerOfTwo (unsigned int x)
{
    return ((x != 0) && !(x & (x - 1)));
}

int isPowerOfFour(unsigned int n)
{
  if(n == 0)
    return 0;
  while(n != 1)
  {    
   if(n%4 != 0)
      return 0;
    n = n/4;      
  }
  return 1;
}

/* Recursive, square blocks, may be underfull
 *   lin   - linear array of values
 *   start - array index of start in lin
 *   end   - array index of end in lin
 *   zord  - z-order array, 2d, as 1d array because of c annoyances
 *   zx    - starting x coordinate in zord
 *   zy    - starting y coordinate in zord
 *   zw    - overall width of zord; NOT width of current block
 */

void lin2zord_internal(unsigned char *lin, int start, int end, unsigned char *zord, int zx, int zy, int zw)
{
  int length = (end-start+1);
  int len_sqrt = ceil(sqrt(length));
  int len_block = len_sqrt * len_sqrt;
  int l4 = len_block/4; // Size of a quarter
  printf("internal %d..%d, %d,%d:%d, %d %d %d %d\n", start, end, zx, zy, zw, length, len_sqrt, len_block, l4);
  if (length <=4) {
    switch (length) {
      case 4:
      printf("Base case 4 %c\n", lin[start+3]);
      *(zord+(zx+1)+(zy+1)*zw) = lin[start+3];
      case 3:
      printf("Base case 3 %c\n", lin[start+2]);
      *(zord+(zx+0)+(zy+1)*zw) = lin[start+2];
      case 2:
      printf("Base case 2 %c\n", lin[start+1]);
      *(zord+(zx+1)+(zy+0)*zw) = lin[start+1];
      case 1:
      printf("Base case 1 %c\n", lin[start+0]);
      *(zord+(zx+0)+(zy+0)*zw) = lin[start+0];
    }
  } else {
    printf("(int)ceil(%d/%d) = %d\n", length, len_block, (int)ceil(length/l4));
    switch ((int)ceil(length/l4)) {
      case 4:
      printf("Maze case 4\n");
      lin2zord_internal(lin, start, start+l4-1, zord, zx, zy, zw);
      case 3:
      printf("Maze case 3\n");
      lin2zord_internal(lin, start+l4, start+2*l4-1, zord, zx+len_sqrt/2, zy, zw);
      case 2:
      printf("Maze case 2\n");
      lin2zord_internal(lin, start+2*l4, start+3*l4-1, zord, zx, zy+len_sqrt/2, zw);
      case 1:
      printf("Maze case 1\n");
      lin2zord_internal(lin, start+3*l4, end, zord, zx+len_sqrt/2, zy+len_sqrt/2, zw);
    }
  }
}


int lin2zord(unsigned char *lin, unsigned char *zord, int n, int zw)
{
  int i;
  if (!isPowerOfTwo(zw)) return -1; // Don't even try to correct bad widths
  if (zw*zw == n) { // Square
    printf("Square\n");
    lin2zord_internal(lin, 0, n-1, zord, 0, 0, zw);
  } else if (zw*zw < n) { // Tall
    printf("Tall\n");
    // Repeat down to reach n
    for (i = 0; (i+1)*zw*zw < n; i++) {
      lin2zord_internal(lin, i*zw*zw, (i+1)*zw*zw-1, zord, 0, i*zw, zw);
    }
    lin2zord_internal(lin, i*zw*zw, n-1, zord, 0, i*zw, zw);
  } else { // zw*zw > n  // Wide
    printf("Wide\n");
    // Height is the largest power of two less than n
    // Repeat across to reach zw
  }
  return 0;
}

/*
 0145
 2367
 89CD
 ABEF
*/
