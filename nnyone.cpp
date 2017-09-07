#include "connect4.h"

class Coord//basic 2d cartesian coordinates class
{
public:
	int x;
	int y;
	bool equals(Coord c)
	{
		if (x == c.x && y == c.y)
			return true;
		return false;
	}
};

int nnyone()//create triangles on a grid out of 2 points with integer coordinates and the origin
{//find how many right triangles can be made with uniques coordinates when 0 <= x1,x2,y1,y2 <= 50
	const int size = 50;
	long long rTris = 0;
	Coord o{ 0,0 };
	for (int x1 = 0; x1 <= size; x1++)
	{
		for (int y1 = 0; y1 <= size; y1++)
		{
			Coord a{ x1,y1 };
			if (a.equals(o))
				continue;
			for (int x2 = 0; x2 <= size; x2++)
			{
				for (int y2 = 0; y2 <= size; y2++)
				{
					Coord b{ x2,y2 };
					if (b.equals(o) || b.equals(a))
						continue;
					long long a2 = a.x*a.x + a.y*a.y;//length of a to o squared
					long long b2 = b.x*b.x + b.y*b.y;//length of b to o squared
					long long c2 = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);//length of a to b squared
					vector<long long> sides = { a2,b2,c2 };//can't tell which is hyp
					sort(sides.begin(), sides.end());//so sort since hyp is always longest
					if (sides[0] + sides[1] == sides[2])//(sides are already squared)
						rTris++;
				}
			}
		}
		cout << x1 << endl;//used to display program progress
	}
	cout << endl << rTris / 2 << endl;//couldn't keep points a&b from switching so double counting all triangles

	return 0;
}