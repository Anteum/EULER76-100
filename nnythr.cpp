#include "connect4.h"
#include "exprtk.hpp"//C++ Mathematical Expression Toolkit Library (ExprTk) //http://www.partow.net/programming/exprtk/

int nnythr()//using 4 different digits once each, +,-,*,/,(, and ), create all possible expressions
{//find the digits whose expressions can equal the most consecutive positive integers starting with 1
	exprtk::expression<double> exp;
	exprtk::parser<double> par;
	const double delta = 0.000001;

	for (int a = 1; a <= 6; a++)//digit 1
	{
		for (int b = a + 1; b <= 7; b++)//digit 2
		{
			for (int c = b + 1; c <= 8; c++)//digit 3
			{
				for (int d = c + 1; d <= 9; d++)//digit 4
				{
					vector<int> digs = { a,b,c,d };//put digits in vector
					vector<bool> expnum(3025, false);//indices are possible integer results of expressions (max is 3024=9*8*7*6)
					vector<char> ops = { '+','-','*','/' };//vector of operations
					for (int x : digs)
						cout << x << ' ';
					for (int x = 0; x <= 3; x++)//first operation chosen
					{
						for (int y = 0; y <= 3; y++)//operation 2
						{
							for (int z = 0; z <= 3; z++)//operation 3
							{
								for (int p = 0; p <= 10; p++)//all distinct parentheses possibilities for 4 digits and 3 operations
								{
									string p1 = "", p2 = "", p3 = "", p4 = "", p5 = "", p6 = "";
									switch (p)
									{
									case 0:	p1 = "(", p3 = ")";
										break;
									case 1:	p2 = "(", p5 = ")";
										break;
									case 2: p4 = "(", p6 = ")";
										break;
									case 3:	p1 = "(", p5 = ")";
										break;
									case 4:	p2 = "(", p6 = ")";
										break;
									case 5:	p1 = "(", p3 = ")", p4 = "(", p6 = ")";
										break;
									case 6:	p1 = "((", p3 = ")", p5 = ")";
										break;
									case 7: p2 = "((", p5 = ")", p6 = ")";
										break;
									case 8:	p1 = "(", p2 = "(", p5 = "))";
										break;
									case 9:	p2 = "(", p4 = "(", p6 = "))";
										break;
									default://no parentheses
										break;
									}
									do
									{
										string strexp = p1 + to_string(digs[0]) + ops[x] + p2 + to_string(digs[1]) + p3 + ops[y] + p4 + to_string(digs[2]) + p5 + ops[z] + to_string(digs[3]) + p6;
										par.compile(strexp, exp);//ExprTk magic
										double sol = exp.value();
										double test = fmod(sol, 1);//test is the decimal part of solution
										if (test<delta || test - 1>-delta)//check if decimal is basically a whole (possible rounding error)
										{
											int target = int(round(sol));
											if (target > 0)//don't go to negative vector index...
												expnum[target] = true;
										}

									} while (next_permutation(digs.begin(), digs.end()));//try every ordering of the digits
								}
							}
						}
					}
					int n;
					for (n = 1; expnum[n] == true; n++) {}
					n--;
					cout << ' ' << n << endl;
				}
			}
		}
	}

	return 0;
}