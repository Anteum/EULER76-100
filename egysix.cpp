#include "connect4.h"

double pathDist(int a, int b, int c, double x)//calculates distance along cuboid between opposite corners
{//a,b,c are lengths of sides, x is distance along the edge of length a where the path crosses
	return sqrt(b*b + x*x) + sqrt(c*c + (a - x)*(a - x));
}

int egysix()//consider cuboids and the shortest paths from one corner to the opposite corner travelling along the surfaces
{//find the min value so that the amount of cuboids with sides up to that value whose shortest path is an integer > 1 000 000
	const double delta = 0.000001;
	for (int max = 1817; ; max++)//starting max has been moved next to solution for speed
	{
		int intLengths = 0;
		for (int a = 1; a <= max; a++)//a <= b <= c to prevent cuboid size repeats
		{
			for (int b = a; b <= max; b++)
			{
				for (int c = b; c <= max; c++)
				{
					double minPath = a + b + c;//the final min path should always be less than this
					double x = double(a*b) / (b + c);//formula here for x is where the distance function is at a minimum when the edge crossed by the path has length a
					double testPath = pathDist(a, b, c, x);//up to 3 unique shortest path candidates, each one crossing an edge parallel to a different axis
					if (testPath < minPath)
						minPath = testPath;
					x = double(c*a) / (a + b);
					testPath = pathDist(c, a, b, x);
					if (testPath < minPath)
						minPath = testPath;
					x = double(b*c) / (c + a);
					testPath = pathDist(b, c, a, x);
					if (testPath < minPath)
						minPath = testPath;
					double test = fmod(minPath, 1);
					if (test<delta || test - 1>-delta)//integer test
						intLengths++;
				}
			}
		}
		cout << max << "  " << intLengths << endl;
		if (intLengths > 1000000)
			break;
	}

	return 0;
}