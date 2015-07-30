instring="ASDFGHJK"
oustring=""

def isPowerOfTwo(n):
        "Is n a power of two"
        return ((n !=0) && !(n & (n - 1)))

def lin2zord(lin):
        "Transforms a linear array into a Z-order 2 dimensional array."
        zord=[][]
        if (isPowerOfTwo(len(lin)))
                lin2zord_internal(lin, 0, len(lin)-1, zord, 0, 0)
        return zord

def lin2zord_internal(lin, start, end, zord, zx, zy):
        length = end-start
        if (length == 4) # Base case Z
                zord[zx][zy] = lin[start]
                zord[zx+1][zy] = lin[start+1]
                zord[zx][zy+1] = lin[start+2]
                zord[zx+1][zy+1] = lin[start+3]
        else
                lin2zord_internal(lin, start, start+length/4, zord, zx, zy);
                lin2zord_internal(lin, start+length/4, start+length/2, zord, zx+length/4, zy);
                lin2zord_internal(lin, start+length/2, end-length/4, zord, zx, zy+length/4);
                lin2zord_internal(lin, end-length/4, end, zord, zx+length/4, zy+length/4);

