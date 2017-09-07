#include "connect4.h"
#include "mini-gmp.h"

class SuperPower//basic class for large powers taken to a fraction of their exp
{
public:
	SuperPower(int b, int x, double r)
		:base(b), exp(x), adjRatio(r)
	{
		adjExp = exp*adjRatio;
		adjPower = pow(base, adjExp);
	}
	int base;
	int exp;
	double adjRatio;
	double adjExp;
	double adjPower;
	void dispSP()
	{
		cout.precision(14);
		cout << base << " ^ " << exp << '*' << adjRatio << " = " << adjPower << endl;
	}
};

bool SPsort(SuperPower a, SuperPower b)//sort powers by power asc
{
	return(a.adjPower < b.adjPower);
}

int nnynin()//find the base/exponent pair with the greatest value in the file
{
	unsigned int base, exp, one = 1, maxP;
	ifstream powerfile("base_exp.txt");
	string strbase, strexp;
	vector<SuperPower> powers;
	double ratio = double(1) / 500000;
	for (int p = 1; p <= 1000; p++)
	{
		getline(powerfile, strbase, ',');
		getline(powerfile, strexp);
		base = stoi(strbase);
		exp = stoi(strexp);
		powers.push_back(SuperPower (base, exp, ratio));
		powers.back().adjExp = p;//trick to remember p post-sort		
	}
	sort(powers.begin(), powers.end(), SPsort);
	for (SuperPower sp : powers)
	{
		cout << sp.adjExp << '\t';//pre-sort index
		sp.dispSP();
	}
	////powers are even too large for gmp
	/*//5 min compute...per power
	mpz_t power, max;
	mpz_init(max);
	mpz_set_ui(max, one);
	for (int p = 1; p <= 1000; p++)
	{
		cout << p << ' ';
		getline(powerfile, strbase, ',');
		getline(powerfile, strexp);
		base = stoi(strbase);
		exp = stoi(strexp);
		cout << base << ' ' << exp << endl;
		mpz_init(power);
		mpz_ui_pow_ui(power, base, exp);
		if (mpz_cmp(power, max) > 0)
		{
			mpz_clear(max);
			mpz_init(max);
			mpz_set(max, power);
			maxP = p;
		}
		mpz_clear(power);
	}
	//*/
	powerfile.close();
	//cout << endl << maxP << endl;

	return 0;
}