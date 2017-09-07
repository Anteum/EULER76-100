#include "connect4.h"

class mSquare//Monopoly square class that holds its type based on movement requirements and also a visit log
{
public:
	int type;//0 is general, 1 is community chest, 2 is chance, 3 is RR, 4 is utility
	long long visits = 0;
};

class mBoard//simple vector of mSquares, location index for 1 player, and roll function for movement
{
public:
	int ind = 0;
	void roll(int sides)//virtually roll 2 dice and follow Monopoly rules for movement
	{
		bool done = false;
		static int doubles = 0;
		int dResult1, dResult2;
		dResult1 = rand() % sides + 1;
		dResult2 = rand() % sides + 1;
		if (dResult1 == dResult2)
			doubles++;
		else
			doubles = 0;
		ind += (dResult1 + dResult2);
		ind %= 40;//loop monopoly board
		if (doubles == 3)
		{
			ind = 10;//jail
			doubles = 0;
		}
		if (ind == 30)//go to jail
		{
			ind = 10;//jail
			doubles = 0;
		}
		if (sqVec[ind].type == 2)//chance
		{
			int cResult2 = rand() % 16 + 1;
			switch (cResult2)
			{
			case 1:	ind = 0;//go
				break;
			case 2:	ind = 10;//jail
				doubles = 0;
				break;
			case 3:	ind = 11;//st charles place
				break;
			case 4:	ind = 24;//illinois ave
				break;
			case 5:	ind = 39;//boardwalk
				break;
			case 6:	ind = 5;//reading RR
				break;
			case 7:	case 8:	//2 cards of next RR
				while (sqVec[ind].type != 3)
				{
					ind++;
					ind %= 40;
				}
				break;
			case 9:	//next utility
				while (sqVec[ind].type != 4)
				{
					ind++;
					ind %= 40;
				}
				break;
			case 10:	//go back 3
				ind += 40 - 3;
				ind %= 40;
				break;
			default:
				sqVec[ind].visits++;
				break;
			}
		}
		if (sqVec[ind].type == 1)//community chest
		{
			int cResult1 = rand() % 16 + 1;
			switch (cResult1)
			{
			case 1:	ind = 0;//go
				break;
			case 2:	ind = 10;//jail
				doubles = 0;
				break;
			default:	
				sqVec[ind].visits++;	
				break;
			}
		}
		if (sqVec[ind].type == 0 || sqVec[ind].type == 3 || sqVec[ind].type == 4)
		{
			sqVec[ind].visits++;
		}
		
		if (doubles > 0)
			roll(sides);
	}
	vector<mSquare> sqVec = //set up the board with movement-affecting squares in place
	{ mSquare{ 0 }, mSquare{ 0 }, mSquare{ 1 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 3 }, mSquare{ 0 }, mSquare{ 2 }, mSquare{ 0 }, mSquare{ 0 }
	, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 4 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 3 }, mSquare{ 0 }, mSquare{ 1 }, mSquare{ 0 }, mSquare{ 0 }
	, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 2 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 3 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 4 }, mSquare{ 0 }
	, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 1 }, mSquare{ 0 }, mSquare{ 3 }, mSquare{ 2 }, mSquare{ 0 }, mSquare{ 0 }, mSquare{ 0 } };
};

int egyfor()//if the squares on a Monopoly board are given 2 digit identifiers starting with go as 00 and players always pay to leave jail first chance,
{//the 3 most likely squares to end your turn in order are 10,24,00  //find the corresponding six digits if the dice used were 4-sided
	srand(time(NULL));//random number generator initialization
	double totalVisits = 0;
	mBoard m1;
	for (int i = 0; i < 1000000; i++)//1 000 000 is arbitrary large number of turns
		m1.roll(4);//tetrahedron
	for (int i = 0; i < m1.sqVec.size(); i++)
		totalVisits += m1.sqVec[i].visits;
	cout.precision(5);

	for (int i = 0; i < m1.sqVec.size(); i++)
		cout << i << '\t' << m1.sqVec[i].visits / totalVisits << endl;

	return 0;
}