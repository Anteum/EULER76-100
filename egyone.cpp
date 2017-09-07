#include "connect4.h"

int egyone()//find the minimum path sum in the file from the top left element to the bottom right allowing movement down and right
{
	const int max = 80;
	vector<vector<long long>> nodes(max, vector<long long>(max));
	ifstream matrix("matrix.txt");
	for (int row = 0; row < max; row++)//get data from file into 2d vector
	{
		for (int col = 0; col < max; col++)
		{
			string temp;
			if (col == max - 1)
				getline(matrix, temp);
			else
				getline(matrix, temp, ',');
			nodes[row][col] = stoi(temp);
		}
	}
	for (int i = max - 2; i >=0; i--)//last column and row elements have only one direction they can move 
	{//so make those element hold the path sum from them to the end
		nodes[max - 1][i] += nodes[max - 1][i + 1];
		nodes[i][max - 1] += nodes[i + 1][max - 1];
	}
	for (int row = max - 2; row >= 0; row--)//rest of the elements have 2 options to move so make them have the path sum of the min choice
		for (int col = max - 2; col >= 0; col--)
			nodes[row][col] += min(nodes[row + 1][col], nodes[row][col + 1]);
	cout << nodes[0][0] << endl;//at the end the top left element should hold the path sum of the min path to the bottom right

	return 0;
}