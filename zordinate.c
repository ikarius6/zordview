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

void lin2zord_internal(unsigned char *lin, int start, int end, unsigned char *zord, int zx, int zy, int zw)
{
  int ls = sqrt(end-start+1);
  int length = (end-start+1);
  if (length <=4) { // Base case
    switch (length) { // Fallthrough intentional
      case 4:    *(zord+(zx+1)+(zy+1)*zw) = lin[start+3];
      case 3:    *(zord+(zx+0)+(zy+1)*zw) = lin[start+2];
      case 2:    *(zord+(zx+1)+(zy+0)*zw) = lin[start+1];
      case 1:    *(zord+(zx+0)+(zy+0)*zw) = lin[start+0];
    }
  } else if (ls > zw) {
    lin2zord_internal(lin, start,      start+l4-1,   zord, zx,      zy,        zw);
    lin2zord_internal(lin, start+l4,   start+2*l4-1, zord, zx,      zy+ls/2,   zw);
    lin2zord_internal(lin, start+2*l4, start+3*l4-1, zord, zx,      zy+ls,     zw);
    lin2zord_internal(lin, start+3*l4, end,          zord, zx,      zy+3*ls/2, zw);
  } else {
    lin2zord_internal(lin, start,      start+l4-1,   zord, zx,      zy,        zw);
    lin2zord_internal(lin, start+l4,   start+2*l4-1, zord, zx+ls/2, zy,        zw);
    lin2zord_internal(lin, start+2*l4, start+3*l4-1, zord, zx,      zy+ls/2,   zw);
    lin2zord_internal(lin, start+3*l4, end,          zord, zx+ls/2, zy+ls/2,   zw);
  }
}


int lin2zord(unsigned char *lin, unsigned char *zord, int n, int zw)
{
  int i;
  if (!IsPowerofTwo(zw)) return -1; // Don't even try to correct bad widths
  if (zw*zw == n) { // Square
    lin2zord_internal(lin, 0, n-1, zord, 0, 0, zw);
  } else if (zw*zw < n) { // Tall
    // Repeat down to reach n
    for (i = 0; i*zw*zw < n; i++) {
      lin2_zord_internal(lin, i*zw*zw, ,zord,
    }
  } else { // zw*zw > n  // Wide
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
