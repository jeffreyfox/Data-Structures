#include "DP.h"

void testLIS(int argc, char* argv[])
{
	int n = 7, sw = 0, m = 20, seed = 200;
	vector<int> num(n, 0);
	if(sw) {
		srand(seed);
		for(int i = 0; i < n; ++i) num[i] = m*1.0*rand()/RAND_MAX;
	} else {
		int i = 0;
		while(i < n && cin >> num[i++]);
	}

	cout << num << endl;
	
	LIS lis0(num), lis1(num), lis3(num);
	
	lis0.solve0();
	lis1.solve1();
	lis3.solve3();
	
	int l(0);
	vector<int> ret;

	l = lis0.getLISlen();
	ret = lis0.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;

	l = lis1.getLISlen();
	ret = lis1.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;

	l = lis3.getLISlen();
	ret = lis3.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;
}

void testLCS(int argc, char* argv[])
{
	//string x = "abcbdab", y = "bdcaba";
	string x = "10010101", y = "010110110";
	LCS lcs(x, y), lcs2(x, y), lcs3(x, y);
	int l = lcs.LCSLength(), l2 = lcs2.LCSLength2(), l3 = lcs3.LCSLength3();
	cout << "LCS of <" << x << "> and <" << y << "> is <" << lcs.constructLCS() << ">, length = " << l << endl;
	cout << "LCS of <" << x << "> and <" << y << " > has length = " << l2 << endl;
	cout << "LCS of <" << x << "> and <" << y << " > has length = " << l3 << endl;
	lcs.print2D();
	cout << endl;
	lcs2.print2D();
	cout << endl;
	lcs3.print2D();
	cout << endl;
}
