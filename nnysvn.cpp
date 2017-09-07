#include "connect4.h"

int nnysvn()//find last 10 digits of 28433×2^7830457+1
{
	long long massP = 1;
	for (int exp = 1; exp <= 7830457; exp++)
	{
		massP *= 2;
		massP %= 10000000000;//only need last 10 digits throughout
	}
	massP *= 28433;
	massP++;
	massP %= 10000000000;
	cout << massP << endl;

	/*
	vector<short> massP = itov(1);
	for (int exp = 1; exp <= 7830457; exp++)
	{
		massP = multVecAndInt(massP, 2);
		while (massP.size() > 10)
			pop_front(massP);
	}
	massP = multVecs(massP, itov(28433));
	massP = vecPlus(massP);
	while (massP.size() > 10)
		pop_front(massP);
	vPrint(massP);
	//*/

	return 0;
}