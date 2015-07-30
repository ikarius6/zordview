#include "zordinate.h"

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
  int l4 = (end-start+1)/4;
  if (l4 == 1)
  {
    *(zord+(zx+0)+(zy+0)*zw) = lin[start+0];
    *(zord+(zx+1)+(zy+0)*zw) = lin[start+1];
    *(zord+(zx+0)+(zy+1)*zw) = lin[start+2];
    *(zord+(zx+1)+(zy+1)*zw) = lin[start+3];
  } else {
    lin2zord_internal(lin, start,      start+l4-1,   zord, zx,      zy,      zw);
    lin2zord_internal(lin, start+l4,   start+2*l4-1, zord, zx+ls/2, zy,      zw);
    lin2zord_internal(lin, start+2*l4, start+3*l4-1, zord, zx,      zy+ls/2, zw);
    lin2zord_internal(lin, start+3*l4, end,          zord, zx+ls/2, zy+ls/2, zw);
  }
}


int lin2zord(unsigned char *lin, unsigned char *zord, int n, int zw)
{
  if (!isPowerOfFour(n)) return -1;
  lin2zord_internal(lin, 0, n-1, zord, 0, 0, zw);
  return 0;
}

/*
 0145
 2367
 89CD
 ABEF
*/
