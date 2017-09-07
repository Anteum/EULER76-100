#include "connect4.h"

long long squ(int n)//returns square of n
{
	return long long(n)*n;
}
long long cub(int n)//returns cube of n
{
	return long long(n)*n*n;
}
long long tes(int n)//returns "tesseract" of n
{
	return long long(n)*n*n*n;
}

int egysvn()//find amount of numbers < 50 000 000 expressible as a sum of a prime squared, prime cubed, and prime tesseracted
{
	vector<int> primes(1, 2);
	for (int n = 3; n <= 7071; n += 2)//7071 is largest int that squares < 50 000 000
		if (isPrime(n))
			primes.push_back(n);
	const int max = 50000000;
	vector<bool> triples(max, false);
	long long total;
	int count = 0;
	for (int a = 0; a < 908; a++)//908th prime is greatest prime that squares to < 50 000 000
	{
		for (int b = 0; b < 73; b++)//73rd prime is greatest prime that cubes to < 50 000 000
		{
			for (int c = 0; c < 23; c++)//23rd prime is greatest prime that tesseracts to < 50 000 000
			{
				total = squ(primes[a]) + cub(primes[b]) + tes(primes[c]);
				if (total < max)
					triples[total] = true;
			}
		}
	}
	for (bool b : triples)
		if (b == true)
			count++;
	cout << count << endl;

	return 0;
}