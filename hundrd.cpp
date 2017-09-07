#include "connect4.h"

int hundrd()//consider arrangements of discs so that the probability of randomly drawing 2 blue ones is exactly 50%
{//find the first such arrangement that contains over a trillion total discs and how many are blue
	const long long trillion = 1000000000000;
	double root2 = sqrt(2);
	double blues, total = 0;
	cout.precision(15);
	for (int n = 2; total <= trillion; n++)
	{//formulas for integer solutions found with wolfram alpha
		blues = (2 * pow((3 - 2 * root2), n) + root2*pow((3 - 2 * root2), n) + 2 * pow((3 + 2 * root2), n) - root2*pow((3 + 2 * root2), n) + 4) / 8;
		total = (-pow(3 - 2 * root2, n) - root2*pow(3 - 2 * root2, n) - pow(3 + 2 * root2, n) + root2*pow(3 + 2 * root2, n) + 2) / 4;
		cout << blues << '/' << total << " * " << blues - 1 << '/' << total - 1 << " = 1/2" << endl;
	}
	/*//too slow
	double mid = 1 / sqrt(2), mid2 = mid + 0.000000000000001;
	long long total = trillion + 1;
	long long blues = mid*total + 1;
	long long total2 = total - 1, blues2 = blues - 1;
	vector<long long> tFac, bFac, t2Fac, b2Fac, num, den;
	for (;;)//ever
	{
		total2 = total - 1, blues2 = blues - 1;
		tFac = primeFactors(total), bFac = primeFactors(blues);
		t2Fac = primeFactors(total2), b2Fac = primeFactors(blues2);
		num.clear(), den.clear();
		num.reserve(bFac.size() + b2Fac.size()), den.reserve(tFac.size() + t2Fac.size());
		num.insert(num.end(), bFac.begin(), bFac.end()), num.insert(num.end(), b2Fac.begin(), b2Fac.end());
		den.insert(den.end(), tFac.begin(), tFac.end()), den.insert(den.end(), t2Fac.begin(), t2Fac.end());
		for (int n = 0; n < num.size(); n++)
		{
			for (int d = 0; d < den.size(); d++)
			{
				if (num[n] == den[d])
				{
					num.erase(num.begin() + n);
					den.erase(den.begin() + d);
					n--;
					break;
				}
			}
		}
		cout << blues << " / " << total << endl;
		vPrint(num), vPrint(den);
		cout << '\n';
		if (den.size() == 1 && den.back() == 2)
			break;
		if (double(blues) / (total - 1) < mid2)
			blues++;
		else
			total++;
		while (double(blues - 1) / (total - 1) > mid2 || double(blues) / total < mid)
		{
			if (double(blues - 1) / (total - 1) > mid2)
			{
				total++;
			}
			if (double(blues) / total < mid)
			{
				blues++;
			}
		}
	}
	cout << blues << endl;
	//*/
	return 0;
}