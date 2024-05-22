#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){
	registerTestlibCmd(argc, argv);
	const string sECReT_oUtPUT = "a9100fda0a7059a979d560b8550f715d4ee391ff9b8b680b2f87b26a69ee5a5e";
	if(ouf.readToken() != sECReT_oUtPUT) quitf(_wa, "Wrong Output Format(Program is killed unexpectedly).");
	long long usr_ans = ouf.readLong(-1, 1000000000000000000);
    long long std_ans = ans.readLong(-1, 1000000000000000000);
	if (usr_ans != std_ans)
	  quitf(_wa, "Wrong Answer.");
	if(ouf.readToken() != sECReT_oUtPUT) quitf(_wa, "Wrong Output Format(Program is killed unexpectedly).");
	quitf(_ok, "Correct.");
	return 0;
}
