#include "connect4.h"
#include "classes.h"

int egythr()//find the minimum path sum in the file from the top left element to the bottom right allowing movement up, down, left, and right
{
	const int max = 80;
	vector<vector<long long>> nodes(max, vector<long long>(max));
	ifstream matrix("matrix.txt");
	for (int row = 0; row < max; row++)//input from file into 2d vector
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
	GridGraph graph(max,max);
	for (int row = 0; row < max; row++)
	{
		for (int col = 0; col < max; col++)
		{
			graph.grid[row][col] = WeightedNode{ nodes[row][col],row,col };//make a graph of weighted nodes out of a 2d vector of nodes
			if (row > 0)
				graph.grid[row][col].u = true;//tell each node the directions its capable of moving
			if (row < max - 1)
				graph.grid[row][col].d = true;
			if (col > 0)
				graph.grid[row][col].l = true;
			if (col < max - 1)
				graph.grid[row][col].r = true;
		}
	}
	cout << dijkstraPath(graph, 0, 0, 79, 79) << endl;//hard work done here

	return 0;
}