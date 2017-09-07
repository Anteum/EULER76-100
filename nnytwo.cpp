#include "connect4.h"

long long sqDig(long long n)
{
	long long total = 0;
	vector<short> nVec = itov(n);
	for (short x : nVec)
		total += x*x;
	return total;
}

int nnytwo()//create chains of numbers by summing the square of each digit of the last number to make the next
{//every chain ends with 1 or 89; find how many chains starting under 10 000 000 end with 89
	int egynins = 0;
	vector<int> ends(568,0);//max 2nd link in chain is 567
	for (int n = 1; n < ends.size(); n++)//so find end for each 2nd link
	{
		int chain = n;
		while (chain != 1 && chain != 89)
			chain = sqDig(chain);
		ends[n] = chain;
	}
	for (int n = 1; n < 10000000; n++)//find end of any start by finding 2nd link and skip to end 
	{
		int y = sqDig(n);
		if (ends[y] == 89)
			egynins++;
	}
	cout << egynins << endl;

	return 0;
}