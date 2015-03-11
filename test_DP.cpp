#include "DP.h"

void testDP(int argc, char* argv[])
{
	//string x = "abcbdab", y = "bdcaba";
	string x = "10010101", y = "010110110";
	LCS lcs(x, y);
	int l = lcs.LCSLength();
	cout << "LCS of <" << x << "> and <" << y << "> is <" << lcs.constructLCS() << ">, length = " << l << endl;
	lcs.print2D();
}
