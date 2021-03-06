#include "DP.h"

ostream& operator<<(ostream& os, const vector<double>& vec) {
	os << "( ";
	for(unsigned k = 0; k < vec.size(); ++k) os << vec[k] << " ";
	os << ")";
	return os;
}

ostream& operator<<(ostream& os, const vector<int>& vec) {
	os << "( ";
	for(unsigned k = 0; k < vec.size(); ++k) os << vec[k] << " ";
	os << ")";
	return os;
}

void testRodCutting(int argc, char* argv[])
{
	int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	vector<int> pp(p, p+11);
	for(int k = 1; k <= 10; ++k) { //length of rod being cut
		RodCutting rc(k, pp), rc2(k, pp);
		int rev = rc.solveBotUp();
		int rev2 = rc2.solveTopDn();
		cout << "Maximum revenue of cutting rod of length " << k << " is " << rev << " ";
		rc.printSol();
		cout << endl;
		cout << "Maximum revenue of cutting rod of length " << k << " is " << rev2 << " ";
		rc2.printSol();
		cout << endl;
	}
}

void testMatrixChainMultiply(int argc, char* argv[])
{
	//Dimensions for A1 .. A6
	int d[7] = {30, 35, 15, 5, 10, 20, 25};
	vector<int> dim(d, d+7);
	MatrixChainMultiply mcm(dim);
	int mc = mcm.solve();
	cout << "Minimum cost of matrix chain multiplication is " << mc << endl;
	mcm.printSol();
	cout << endl;
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
	
	LIS lis0(num), lis1(num), lis2(num);
	
	lis0.solve0();
	lis1.solve1();
	lis2.solve2();
	
	int l(0);
	vector<int> ret;

	l = lis0.getLISlen();
	ret = lis0.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;

	l = lis1.getLISlen();
	ret = lis1.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;

	l = lis2.getLISlen();
	ret = lis2.getLISvec();
	cout << "LIS length = " << l << " " << ret << endl;
}

void testOptBST(int argc, char* argv[])
{
	int n = 5; //five keys
	double p[] = {0.15, 0.10, 0.05, 0.10, 0.20};
	double q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
	vector<double> pp(p, p+n), qq(q, q+n+1);
	OptBST obst(n, pp, qq), obst1(n, pp, qq);
	obst.solve(0);	obst1.solve(1);
	cout << "cost of optimum BST is " << obst.c[0][n] << endl << endl;
	obst.printTree();
	
	cout << "cost of optimum BST is " << obst1.c[0][n] << endl << endl;
	obst1.printTree();

	cout << "cost matrix is" << endl;
	for(int k = 0; k < obst.c.size(); ++k) 
		cout << obst.c[k] << endl;
	cout << endl;

	cout << "weight matrix is" << endl;
	for(int k = 0; k < obst.w.size(); ++k) 
		cout << obst.w[k] << endl;
	cout << endl;

	cout << "root matrix is" << endl;
	for(int k = 0; k < obst.r.size(); ++k) 
		cout << obst.r[k] << endl;
	cout << endl;
}

void testPalindrome(int argc, char* argv[])
{
	string str[] = {"mississippi", "abdbacfcabdbade", "aaaaa", "accbcbbcabacbacbccac", 
		"121222212121212121222211211212111212", "abcde", "aaaab"};
	for(int k = 0; k < 7; ++k) {
		string s = str[k];
		LongestPalindrome lp(s), lp2(s);
		string ss = lp.solve();
		string ss2 = lp2.solve2();
		cout << "Longest palindrome of '" << s << "' is '" << ss << "' " <<endl;	
		cout << "Longest palindrome of '" << s << "' is '" << ss2 << "' " <<endl;	

		PalindromePartition pp(s), pp2(s);
		int mc = pp.solve(), mc2 = pp2.solve2();
		cout << "Minium partition cut of '" << s << "' is '" << mc << "' " << endl;
		pp.printSol();
		cout << endl;
		cout << "Minium partition cut of '" << s << "' is '" << mc2 << "' " << endl;
		pp2.printSol();
		cout << endl;
	}
}

void testEditDistance(int argc, char* argv[])
{
	string x = "kitten", y = "sitting";
	EditDistance ed(x, y);
	int d = ed.solve();
	cout << "Edit of <" << x << "> and <" << y << "> is " << d << endl;
}

void testBinomialCoeff(int argc, char* argv[])
{
	int n = 8, k = 3;
	BinomialCoeff bc(n, k);
	cout << "C("<<n<<", "<<k<<") = "<<bc.solve()<<endl;
}

void testEggDrop(int argc, char* argv[])
{
	int n = 2, k = 100;
	EggDrop ed(n, k);
	int nt = ed.solve();
	cout << "Egg drop, " << n << " eggs and " << k << " floors, minimum number of trials = " << nt << ", first drop = " << ed.firstDrop() << endl;
}

void testCoinChange(int argc, char* argv[])
{
	int n = 7;
	int s[] = {1, 2, 3, 4, 5};
	vector<int> ss(s, s+ sizeof(s)/sizeof(int));
	CoinChange cc(n, ss);
	CoinChange cc2(n, ss);
	int count = cc.solveBotUp();
	int count2 = cc2.solveTopDn();
	cout << " n = " << n << ", array = " << ss << endl;
	cout << " count = " << count <<endl;
	cout << " count = " << count2 <<endl;
	cout << " Bottom up executed " << cc.counter << " times " << endl;
	cout << " Top down executed " << cc2.counter << " times " << endl;
}

