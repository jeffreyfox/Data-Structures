#include "bitwise.h"

void testBit(int argc, char* argv[])
{
	unsigned x = 23;
	unsigned y = swapBits(x);
	cout << " " << dec2bin(x) << " " << x << " swapped as " <<endl;
	cout << " " << dec2bin(y) << " " << y << endl;
	
	x = 16;
	if(isPowerOfTwo(x)) cout << " " << dec2bin(x) << " " << x << " is power of two " << endl;
	else cout << " " << dec2bin(x) << " " << x << " is NOT power of two " << endl;

	int z = 1324987; 
	cout << " " << dec2bin(z) << " " << z << " has " << numSetBits(z) << " 1s" <<endl;
	cout << " " << dec2bin(z) << " " << z << " has " << numSetBits2(z) << " 1s" <<endl;

	int i = 2, j = 5;
	unsigned p = setBits(i, j);
	cout << "p = " << dec2bin(p) << " " << p << endl;
	unsigned kk = 0;
	p = setBits2(i, j);
	cout << "p = " << dec2bin(p) << " " << p << endl;

	i = 2, j = 31;
	int n = 1024, m = ~0;
	cout << " i = " << i << " j = " << j << endl;
	cout << "m = " << dec2bin(m) << " " << m << endl;
	cout << "n = " << dec2bin(n) << " " << n << endl;
	int q = updateBits(n, m, i, j);
	cout << "q = " << dec2bin(q) << " " << q << endl;
	q = updateBits2(n, m, i, j);
	cout << "q = " << dec2bin(q) << " " << q << endl;

	m = 127;
	n = nextHigher(m);
	p = nextHigher2(m);
	q = nextLower(m);
	cout << "m = " << dec2bin(m) << " " << m << endl;
	cout << "n = " << dec2bin(n) << " " << n << endl;
	cout << "p = " << dec2bin(p) << " " << p << endl;
	cout << "q = " << dec2bin(q) << " " << q << endl;
}
