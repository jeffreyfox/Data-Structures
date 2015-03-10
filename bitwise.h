#ifndef BITWISE_H
#define BITWISE_H


namespace BitLib {

	string bin2str(unsigned n) {
		unsigned int l = 1;
		string str(32, '0');
		for(unsigned i = 0; i < 32; ++i) {
			if(l & n) str[31-i] = '1';
			l = l << 1;
		}
		return str;
	}

	string bin2str(int n) {
		unsigned int l = 1;
		string str(32, '0');
		for(unsigned i = 0; i < 32; ++i) {
			if(l & n) str[31-i] = '1';
			l = l << 1;
		}
		return str;
	}

	unsigned int swapBits(unsigned x) {
		return (x & 0xAAAAAAAA) >> 1 | (x & 0x55555555) << 1;
	}

	unsigned char swapNibbles(unsigned char x) {
		return (x & 0xF0) >> 4 | (x & 0x0F) << 4;
	}

	/// Turn off k-th bit (k = 1-32) in x
	unsigned int turnOffK(unsigned int x, unsigned int k) {
		return  x & ~(1 << (k-1));
	}

	/// Calculate number of set bits in an integer by scanning all bits
	int numberOfOne(int x) {
		unsigned int n = 1;
		int count = 0;
		while(n) {
			if(x & n) count ++;
			n <<= 1;
		}
		return count;
	}

	/// Calculate number of set bits in an integer by using minus one
	int numberOfOne2(int x) {
		int count = 0;
		while(x) {
			x = x & (x-1); //turn-off the right most 1
			count++;
		}
		return count;
	}

	bool isPowerOfTwo(unsigned int x) {
		return x && !(x & (x-1));
	}

	/// Return an integer whose bits i to j are 1 and 0 otherwise
	unsigned setBits(unsigned i, unsigned j) {
		int left = (j+1 == 32) ? ~0 : ((1 << j+1) -1); // 0s thru j+1, and 1s from j to 0
		int right = (1 << i) -1; // 0s thru i, and 1s from i-1 to 0  
		return left ^ right; //1s from i to j, and 0 otherwise
	}

	/// Return an integer whose bits i to j are 1 and 0 otherwise
	unsigned setBits2(unsigned i, unsigned j) {
		int left = (j == 31) ? 0 : (~((1<< j+1) - 1));  //1s thru j+1, and 0s from j to 0
		int right = (1 << i)-1; // 0s thru i, and 1s from i-1 to 0 
		return ~(left | right); //1s from i to j, and 0 otherwise
	}

	//update n's bits i to j by m, solution in careercup (wrong)
	int updateBits(int n, int m, int i, int j) {
		int max = ~0; /* All 1's */
		// 1's through position j, then 0's
		int left = max - ((1 << j) - 1);
		// 1's after position i
		int right = ((1 << i) - 1);
		// 1's, with 0s between i and j
		int mask = left | right;
		// Clear i through j, then put m in there
		return (n & mask) | (m << i);
	}

	//update n's bits i to j by m, my solution
	int updateBits2(int n, int m, int i, int j) {
		assert(0 <= i && i <= j && j <= 31); 
		// 1's through position j+1, then 0's
		int left = (j+1 == 32) ? 0 : ~((1 << j+1) - 1);
		// 1's after position i
		int right = ((1 << i) - 1);
		// 1's, with 0s between i and j
		int maskn = left | right;
		//1's after position j-i+1
		int maskm = (1 << j-i) - 1;
		// Clear i through j, then put m in there
		return (n & maskn) | (m & maskm) << i;
	}

	int rightMostSet(int x) {
		unsigned y = x & (~x+1);
		int pos = -1;
		while(y) {
			y >>= 1;
			pos++;
		}
		return pos;
	}

	int nextHigher(int x) {
		if(x <= 0) return -1;
		int n = rightMostSet(x);//first 1
		int m = rightMostSet(~(x >> n)) + n; //first 0 after 1
		x |= (1 << m);  //set d(m)
		x &= ~(1 << m-1); //unset d(m-1)
		int len = m-n-1, mask = (1 << len) - 1;
		if(len > 0) {
			x &= ~(mask << n); //turn off len ones after d(m-1)
			x |= mask; //turn on len zeros from lowest
		}
		return x < 0 ? -1 : x;
	}

	int nextHigher2(int x) {
		int n = x & (~x + 1); //rightmost set bit
		int y = x + n; // 01111000 => 10000000
		int pn = 0; //position of the set bit in n
		while(n) { 	pn ++; n = n >> 1;	} 
		return y | ((x & (y-1)) >> pn);
	}

	int nextLower(int x) {
		if(x <= 0) return -1;
		int n = rightMostSet(~x); //first 0
		int m = rightMostSet(x >> n) + n; //first 1 after 0
		x &= ~(1 << m);  //unset d(m)
		x |= (1 << m-1); //set d(m-1)
		int len = n, mask = (1 << len) - 1;
		if(len > 0) {
			x &= ~mask; //turn off len zeros from lowest
			x |= (mask << m-n-1);//turn on len ones after d(m-1)
		}
		return x < 0 ? -1 : x;
	}

	unsigned int reverseBits(unsigned n) {
		unsigned int lo = 0x00000001, hi = 0x80000000, XOR = 0;
		int d = 31;
		while(lo < hi) { //swap two bits
			XOR = (((n & lo ) << d) ^ (n & hi)) | (((n & hi ) >> d) ^ (n & lo));
			n = n ^ XOR;
			lo = lo << 1;
			hi = hi >> 1;
			d -= 2;
		}
		return n;
	}
};

#endif
