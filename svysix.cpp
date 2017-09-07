#include "connect4.h"


int svysix()//find the number of ways 100 can be written as a sum of natural numbers
{
	cout << partitionsP(100) - 1 << endl;//-1 to subtract inclusion of n itself
											 
	/*//slooooow, found solution overnight
	//const int sum = 100;//100 is too big...
	long long total = 0;
	vector<long long> totals;
	totals.push_back(1);//1 is the # of sum combos of 1 (+1)
	for (int sum = 2; sum < 50; sum++)
	{
		cout << sum << endl;
		vector<vector<short>> sums(0, vector<short>());
		int cur = sum - 1, row = 0, col = 0, temp;
		sums.push_back(vector<short>());
		sums[0].push_back(cur);
		sums[0].push_back(1);
		//cout << cur << endl;
		while (true)
		{
			cur = sums[row].back();
			col = sums[row].size() - 1;
			for (int n = sums[row].size() - 1; n >= 1; n--)
				if (sums[row][n] == 1)
					cur = sums[row][n - 1], col = n - 1;
				else
					break;
			if (cur == 1)
				break;
			sums.push_back(vector<short>());
			cur--;
			row++;
			if (col == 0)
			{
				//cout << cur << endl;
				temp = sum;
			}
			else
			{
				sums[row] = vector<short>(sums[row - 1].begin(), sums[row - 1].begin() + col);
				temp = sum - vSum(sums[row]);
			}
			for (temp; temp >= cur; temp -= cur)
				sums[row].push_back(cur);
			if (temp != 0)
				sums[row].push_back(temp);
		}
		totals.push_back(sums.size() + 1);
	}
	cout << "partially completed." << endl;
	for (long long x : totals)
		total += x;
	cout << total << endl;
	
	int sum = 100;
	vector<short> sums, prev;
	int cur = sum - 1, col = 0, temp;
	sums.push_back(sum / 2);
	sums.push_back(sum / 2);
	total++;
	while (true)
	{
		cur = sums.back();
		col = sums.size() - 1;
		for (int n = sums.size() - 1; n >= 1; n--)
			if (sums[n] == 1)
				cur = sums[n - 1], col = n - 1;
			else
				break;
		if (cur == 1)
			break;
		prev = sums;
		sums.clear();
		cur--;
		//row++;
		if (col == 0)
		{
			cout << cur << endl;
			temp = sum;
		}
		else
		{
			sums = vector<short>(prev.begin(), prev.begin() + col);
			temp = sum - vSum(sums);
		}
		for (temp; temp >= cur; temp -= cur)
			sums.push_back(cur);
		if (temp != 0)
			sums.push_back(temp);
		total++;
	}
	
	cout << endl << total << endl;
	//*/

	return 0;
}