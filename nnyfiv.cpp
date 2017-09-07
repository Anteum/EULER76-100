#include "connect4.h"

int nnyfiv()//create chains of numbers by going from n to the aliquot sum of n
{//find smallest element of longest chain that returns to start and never exceeds 1 000 000
	const int max = 1000000;//million
	int maxLength = 0, maxsMin;
	vector<int> chain;
	vector<int> pdivsums(max + 1, 0);//sum of proper divisors is the aliquot sum
	for (int n = 1; n <= 500000; n++)//make vector of aliqout sums of all n <= 1 000 000
		for (int mult = 2*n; mult <= max; mult += n)
			pdivsums[mult] += n;
	cout << "aliquoted." << endl;//sum of all divisors of n other than itself is called the aliquot sum
	for (int i = 2; i <= max; i++)//only need to check chains that start <= 1 000 000
	{
		chain.push_back(i);
		bool ouro = false, coiled = false;//here ouro means loops to start, coiled means loops to anywhere
		while(!coiled)//ouro implies coiled as well
		{
			int next = pdivsums[chain.back()];
			if (next > max)
				break;
			if (next == chain.front())
				ouro = true;
			for(int link:chain)
				if (next == link)
				{
					coiled = true;
					break;
				}
			if (!ouro && !coiled)
				chain.push_back(next);
			else
			{
				if (ouro && chain.size() > maxLength)//prospects enter here
				{
					maxLength = chain.size();
					maxsMin = *min_element(chain.begin(), chain.end());//dereference iterator gives value
				}
				chain.clear();
			}
		}
	}
	cout << maxsMin << endl;

	return 0;
}