#ifdef ZORDINATE_H
#define ZORDINATE_H

/*
 * Transform a linear array into a z-order array.
 * All memory must be allocated aforehand.
 *   lin  - a linear array of bytes to be reordered
 *   zord - an array to be loaded in z-order presuming concatinated rows
 *   n    - length of lin, must be a power of 4 currently
 *          XXX Support other lengths
 *   zw   - width of z-order rows to be produced, must be sqrt(n) currently
 *          XXX Support non-square arrays
 */
int lin2zord(unsigned char *lin, unsigned char *zord, int n, int zw);

#endif // ZORDINATE_H
