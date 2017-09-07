#include "connect4.h"

int egyfiv()//create every possible rectangle out of the gridlines in a grid of a particular size
{//find the area of the grid whose possible rectangles is closest to 2 000 000 rectangles
	const int max = 2000000;
	int minDiff = max;
	long long minsArea = 0;
	vector<vector<long long>> subRecs;//same amount of subRecs in m x n grid as n x m grid so this 2d vector is triangular
	vector<long long> starter;
	int tot = 0; 
	for (int i = 1; tot < max; i++)//1 x n grids have sum(k,1,n) possible rectangles
	{
		tot += i;
		starter.push_back(tot);
	}
	subRecs.push_back(starter);

	for (int ind = 1; ind < starter.size(); ind++)//if subRecs is seen as top-right triangular matrix, first element of each row is top element of its column squared
	{//each following element is the same proportion from the last as the corresponding elements in the top row
		vector<long long> temp{};
		temp.push_back(starter[ind] * starter[ind]);
		for (int i = ind; i < starter.size() - 1; i++)
		{
			temp.push_back(temp[i - ind] * starter[i + 1] / starter[i]);
		}
		subRecs.push_back(temp);
	}

	for (int i = 0; i < subRecs.size(); i++)
	{
		for (int j = 0; j < subRecs[i].size(); j++)
		{
			//cout << subRecs[i][j] << '\t';
			if (abs(subRecs[i][j] - max) < minDiff)//go thru all subRecs and look for total closest to 2 000 000
			{
				minDiff = abs(subRecs[i][j] - max);
				minsArea = (i + 1)*(i + 1 + j);
			}
		}
		//cout << '\n';
	}
	cout << minsArea << endl;

	return 0;
}