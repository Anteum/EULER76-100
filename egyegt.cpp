#include "connect4.h"

vector<vector<short>> factorz(short n)//return all factorizations of n besides trivial 1*n
{
	vector<vector<short>> facList;
	vector<short> factors, pFactors = primeFactors(n);//pFactors is the only factorization of its length which is the max
	for (int length = 2; length < pFactors.size(); length++)
	{
		factors = {};
		int curN = n;//keep track of how much is left of n to factorize
		for (int x = 2; ; x++)
		{
			if (curN%x == 0)
			{
				factors.push_back(x);
				curN /= x;
				x--;//try x again
			}
			if (factors.size() == length - 1)
			{
				factors.push_back(curN);
				break;
			}
		}
		facList.push_back(factors);
		factors.pop_back();
		bool done = false;
		while (!done)//one more of same length?
		{
			int last = factors.back();
			curN *= last;
			factors.pop_back();
			for (int x = last + 1; pow(x, length - factors.size()) <= curN; x++)
			{
				if (curN%x == 0)
				{
					factors.push_back(x);
					curN /= x;
					x--;//try x again
				}
				if (factors.size() == length - 1)
				{
					factors.push_back(curN);//
					facList.push_back(factors);
					factors.pop_back();//
					break;
				}
			}
			if (factors.size() == 0)
				done = true;	
		}
	}
	if (pFactors.size() > 1)
		facList.push_back(pFactors);
	return facList;
}

bool vFull(vector<short> v)//check if the vector has no zero values in it
{
	for (int i = v.size() - 1; i >= 0; i--)
		if (v[i] == 0)
			return false;
	return true;
}

int egyegt()//a number expressible by the sum or product of the same list of numbers is a product-sum number (PSN)
{//let the smallest PSN of a given list length be a minimal PSN; find the sum of the unique minimal PSNs for lengths k, 2 <= k <= 12 000 
	const short max = 12000;
	vector<short> minPSNs(max + 1, 0);
	vector<vector<short>> psnFacts;
	minPSNs[0] = -1, minPSNs[1] = -1;//ensure indices 0 & 1 do not receive values and do not appear empty
	for (short psn = 4; !vFull(minPSNs); psn++)//possible PSNs
	{
		psnFacts = factorz(psn);
		for (int f = 0; f < psnFacts.size(); f++)
		{//size of the list of numbers is the amount of factors plus the number of ones needed to bring the sum to equal the PSN
			int k = psnFacts[f].size() + psn - vSum(psnFacts[f]);
			if (k <= max && minPSNs[k] == 0)
				minPSNs[k] = psn;//since PSNs are increasing, first one found for particular list size is smallest
		}
	}
	cout << "\nmin PSNs found.\n" << endl;
	cout << vSum(uniqEle(minPSNs)) + 1 << endl;//+1 to cancel -1 from indices 0 & 1
	//for (short i = 0; i < minPSNs.size(); i++)
		//cout << i << "  " << minPSNs[i] << endl;
	
	return 0;
}