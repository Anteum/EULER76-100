#include "connect4.h"

int svyegt()//let p(n) be the number of ways n coins can be seperated into piles
{//find the first value of n for which p(n) is divisible by 1 000 000
	long long test, n = 0;
	do
	{
		n++;
		test = partitionsPmod(n, 1000000);//uses mod to only keep last 6 digits
		//cout << n << "  " << test << endl;
	} while (test != 0);
	cout << n << endl;

	return 0;
}
//Select[Range[55000,55500],IntegerQ[PartitionsP[#]/100000]&]//(wolfram language)