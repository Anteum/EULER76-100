#include "connect4.h"

int svysvn()//find the first number which can be written as the sum of primes in over 5000 different ways
{
	for (int sum = 10; ; sum++)//in the given example, 10 can be written 5 ways
	{
		vector<bool> primas(sum + 1, false);//primalities
		vector<int> primes;//list of primes up to sum
		primas[2] = true;
		for (int n = 3; n <= sum; n += 2)
			if (isPrime(n))
				primas[n] = true;
		for (int i = 0; i <= sum; i++)
			if (primas[i] == true)
				primes.push_back(i);//create vector of all primes up to the sum

		vector<vector<short>> sums(0, vector<short>());//create empty 2d vector
		int cur = primes.size() - 1, row = 0;//current prime starts with largest //each row contains unique sum
		sums.push_back(vector<short>());//put an empty vector into sums
		sums[0].push_back(primes.back());//put largest prime in primes in empty vector
		//*
		while (true)
		{
			while (vSum(sums[row]) + primes[cur] <= sum)//while adding the current prime does not exceed sum
				sums[row].push_back(primes[cur]);//put a current prime into the current row
			if (cur == 0 || vSum(sums[row]) == sum)//if cur is 0 all primes have been attempted (fail) //if the primes sum to the sum (success)
			{
				if (sums[row][0] == 2)//if the leading number in the current row is 2, all prime combinations have been summed (done)
					break;
				if (vSum(sums[row]) == sum)//if last row was a success, 
				{
					sums.push_back(sums[row]);//make copy
					row++;//go to new row
				}
				while (sums[row].back() == 2)//remove all 2's from prime sum since there is no smaller prime to finish sum with
					sums[row].pop_back();
				while (sums[row].back() != primes[cur])//readjust so the current prime is the last prime in the sum
					cur++;
				sums[row].pop_back();//remove 1 extra from end of prime sum so the program will make a different sum from it
				//cur--;//go back to next smallest prime
				//continue;
			}
			//if (vSum(sums[row]) < sum)//if the prime sum is less than sum (not done)
			cur--;//current prime is next smallest
		}
		//*/
		//for (int r = 0; r < sums.size(); r++)
			//vPrint(sums[r]);
		cout << sum << "  " << sums.size() << endl;//display info
		if (sums.size() > 5000)
			break;
	}

	return 0;
}