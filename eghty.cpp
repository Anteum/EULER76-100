#include "connect4.h"

int eghty()//the square root of an integer that is not square is irrational
{//find the sum of the first 100 digits of the roots of the first 100 integers that are irrational
	long long total = 0;
	vector<short> root;
	for (int n = 1; n <= 100; n++)
	{
		double test = sqrt(n);
		if (test == int(test))//do not count square numbers' roots
			continue;
		root = preciSqrt(n, 99);//all irrational roots of integers <= 100 will have integer part of 1 digit (need 99 digits after decimal)
		total += vSum(root);
		cout << n << '\n';
	}
	cout << total << endl;
	return 0;
}
