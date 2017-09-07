#include "connect4.h"

class WeightedNode//nodes with cost as you pass thru that fit in a grid
{
public:
	long long weight;//cost of movement thru node
	int y;//nodes coordinates
	int x;
	bool u = false;//movement directions
	bool r = false;
	bool d = false;
	bool l = false;
	long long pathSum = 9223372036854775807;//"infinity"
	bool visited = false;
	bool equals(WeightedNode n2)
	{
		if (n2.x == x && n2.y == y)
			return true;
		return false;
	}
};

class GridGraph//grid made of nodes
{
public:
	GridGraph(int r, int c)
		:rows{ r }, cols{ c }
	{
		grid = vector<vector<WeightedNode>>(rows, vector<WeightedNode>(cols));
	}
	vector<vector<WeightedNode>> grid;

private:
	int rows;
	int cols;

};

class NodeList//a list of nodes sorted by its path sum from start
{
public:
	vector<WeightedNode> nList;
	void pushNode(WeightedNode n)//adds to list with low weights at back
	{
		if (nList.size() == 0)
			nList.push_back(n);
		else
		{
			int ind = nList.size() - 1;
			while (ind >= 0 && n.pathSum > nList[ind].pathSum)
				ind--;
			nList.insert(nList.begin() + (ind + 1), n);//ind + 1 requires parentheses!...crashes w/o
		}
	}
}; 
