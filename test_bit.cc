#include "bitwise.h"

void testBit(int argc, char* argv[])
{
	unsigned x = 23;
	unsigned y = swapBits(x);
	cout << " " << bin2str(x) << " " << x << " swapped as " <<endl;
	cout << " " << bin2str(y) << " " << y << endl;
	x = 20387;
	unsigned k = 6;
	y = turnOffK(x, k);
	cout << " " << bin2str(x) << " " << x << " turn off bit " << k << " becomes " <<endl;
	cout << " " << bin2str(y) << " " << y << endl;
	x = 1;
	if(isPowerOfTwo(x)) cout << " " << bin2str(x) << " " << x << " is power of two " << endl;
	else cout << " " << bin2str(x) << " " << x << " is NOT power of two " << endl;
	int z = 1324987; 
	cout << " " << bin2str(z) << " " << z << " has " << numberOfOne(z) << " 1s" <<endl;
	cout << " " << bin2str(z) << " " << z << " has " << numberOfOne2(z) << " 1s" <<endl;

	x = 128+64+32+1024;
	y = findHigher(x);
	cout << "x = " << bin2str(x) << " " << x << endl;
	cout << "y = " << bin2str(y) << " " << y << endl;
	z = x&(~x+1);
	cout << "z = " << bin2str(z) << " " << z << endl;

	int i = 2, j = 5;
	unsigned p = setBits(i, j);
	cout << "p = " << bin2str(p) << " " << p << endl;
	unsigned kk = 0;
	p = setBits2(i, j);
	cout << "p = " << bin2str(p) << " " << p << endl;
}
