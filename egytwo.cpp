#include "connect4.h"
#include "classes.h"


int egytwo()//find the minimum path sum in the file from a first column element to a last column element allowing movement up, down, and right
{
	const int max = 80;
	vector<vector<long long>> nodes(max, vector<long long>(max));
	ifstream matrix("matrix.txt");
	for (int row = 0; row < max; row++)//input elements in file into 2d vector
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
	matrix.close();
	GridGraph graph(max, max);
	for (int row = 0; row < max; row++)//make a graph of nodes out of 2d vector
	{
		for (int col = 0; col < max; col++)
		{
			graph.grid[row][col] = WeightedNode{ nodes[row][col],row,col };
			if (row > 0)
				graph.grid[row][col].u = true;//give allowed movements
			if (row < max - 1)
				graph.grid[row][col].d = true;
			if (col < max - 1)
				graph.grid[row][col].r = true;
		}
	}
	long long min = 9223372036854775807;//infinity
	
	for (int rowa = 0; rowa < max; rowa++)//find path sums for every path from left side to right
	{
		for (int rowb = 0; rowb < max; rowb++)
		{
			if (abs(rowa - rowb) > 10)//restrict to paths whose start and finish only vary by <= 10 rows
				continue;//(skipped paths are longer so less likely to have min path sum)
			long long temp = dijkstraPath(graph, rowa, 0, rowb, 79);
			if (temp < min)
				min = temp;
			cout << rowa << ':' << rowb << ' ' << temp << endl;
		}
	}
	cout << min << endl;
	
	/*
	vector<vector<long long>> strPaths = nodes;
	for (int row = 0; row < max; row++)
		for (int col = max - 2; col >= 0; col--)
			strPaths[row][col] += strPaths[row][col + 1];
	//for (vector<long long> x : strPaths)
		//cout << x[0] << endl;
	long long minPath = 349326;//straight path min

	for (int row = 0; row < max; row++)
	{
		
		long long path = nodes[row][0] + nodes[row][1];
		int curRow = row;
		bool up = true;
		for (int col = 1; col < max - 1; col++)
		{
			if (curRow > 0 && curRow < max - 1 && strPaths[curRow + 1][col] < strPaths[curRow - 1][col])
				up = true;
			else
				up = false;
			if (curRow < max - 1 && strPaths[curRow + 1][col] < strPaths[curRow][col + 1] && up)// && 
			{
				path += nodes[curRow + 1][col];
				curRow++;
				col--;
			}
			else if (curRow > 0 && strPaths[curRow - 1][col] < strPaths[curRow][col + 1])// && strPaths[curRow - 1][col] <= strPaths[curRow + 1][col])
			{
				path += nodes[curRow - 1][col];
				curRow--;
				col--;
			}
			else
				path += nodes[curRow][col + 1];
		}
		if (path < minPath)
			minPath = path;
	}
	cout << minPath << endl;
	//*/


	return 0;
}