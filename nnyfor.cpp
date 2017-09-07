#include "connect4.h"
#include "mini-gmp.h"

class LongDouble//attempt at vector version of double
{
public:
	vector<short> sig;//significand
	int exp = 0;
	short& operator[](const int ind)//overload operator!
	{
		return sig[ind];
	}
	void disp()
	{
		for (short x : sig)
			cout << x << ' ';
		cout << "E" << exp << endl;
	}
};

LongDouble dtoLD(double d)
{
	LongDouble dd;
	int exp = 0;
	while (d >= 10)
	{
		d /= 10;
		exp++;
	}
	while (d < 1)
	{
		d *= 10;
		exp--;
	}
	for (int dig = 1; dig <= 14; dig++)
	{
		int temp = d;
		dd.sig.push_back(temp);
		d -= temp;
		d *= 10;
	}
	while (dd.sig.back() == 0)
		dd.sig.pop_back();
	/*//rounding...
	bool round=false;
	if(dd.sig.size()>7)
	{
		for(int i=1;i<=7;i++)
			if(dd[dd.sig.size()-i]==9)
				round=true;
			else
			{
				round=false;
				break;
			}
		if(round)
		{
			while(dd.sig.back()==9&&dd.sig.size()>0)
				dd.sig.pop_back();
			if(dd.sig.size()==0)
				dd.sig.push_back(1);
			else
				dd.sig.back()++;
		}
		
	}
	//*/
	dd.exp = exp - dd.sig.size() + 1;
	return dd;
}

LongDouble preciSqrt(LongDouble dd, int precision)
{
	LongDouble root;// nVec[] is now dd[] and nVec. is dd.sig.
	vector<short> cur, left;
	int x, ind = 0, ddSize = dd.sig.size();
	cur.push_back(dd[ind++]);
	if (dd.sig.size() % 2 == 0)
		cur.push_back(dd[ind++]);
	for (int d = 1; d <= precision * 2 + 2; d++)//?//////less maybe
		dd.sig.push_back(0);

	for (x = 1; (x + 1)*(x + 1) <= vtoi(cur); x++)
	{}
	root.sig.push_back(x);
	left = itov(2 * x);
	cur = itov(vtoi(cur) - x*x);
	while (root.sig.size() < precision)//(ind < dd.sig.size() - 2)
	{
		cur.push_back(dd[ind++]);
		cur.push_back(dd[ind++]);
		left.push_back(-1);
		for (int d = 1; d <= 10; d++)
		{
			left.back()++;
			if (vIsGreater(multVecs(vecPlus(left), itov(d)), cur))
			{
				root.sig.push_back(d - 1);
				cur = diffVecs(cur, multVecs(left, itov(d - 1)));
				left = multVecs(root.sig, itov(2));
				break;
			}
		}
	}
	if (dd.exp % 2 != 0)
	{
		dd.exp++;
		root.sig = multVecs(root.sig, preciSqrt(10, 10));
		vector<short> temp(root.sig.begin(), root.sig.begin() + precision);
		root.sig = temp;
	}
	root.exp = int((ddSize + dd.exp) / 2.0 + 0.5) - precision;
	return root;
}

LongDouble heron(int a, int b, int c, int p)
{
	double s = (a + b + c) / 2.0;
	LongDouble ss = dtoLD(s), sa = dtoLD(s - a), sb = dtoLD(s - b), sc = dtoLD(s - c);
	int cut = abs(ss.exp + sa.exp + sb.exp + sc.exp);
	vector<short> temp = multVecs(multVecs(ss.sig, sa.sig), multVecs(sb.sig, sc.sig));
	for (int i = 1; i <= cut; i++)
		temp.pop_back();
	LongDouble area2{ temp };
	return preciSqrt(area2, p);
}

double heron(int a, int b, int c)
{
	double s = (a + b + c) / 2.0;
	return sqrt(s*(s - a)*(s - b)*(s - c));
}

int nnyfor()//let an almost equilateral triangle (AET) be a tri with 2 equal sides and a third up to one unit off
{//find the sum of all AETs with integral sides and area and perimeter <= 1 000 000 000
	const int billion = 1000000000;
	int perims = 0;
	for (int u = 2; 4 * u*u <= billion; u++)//4u^2 is the perimeter
	{
		for (int v = 1; v < u; v++)
		{
			if (gcd(u, v) != 1)//prereq of the formula
				continue;
			int a = 2 * (u*u - v*v);//formulas from wiki on integer triangles, isosceles heronian
			int b = u*u + v*v;
			int c = b;
			int q = gcd(a,b);//gcd(a,b)=gcd(a,b,c) here
			a /= q, b /= q, c /= q;//divide by gcd(a,b,c) to become primitive which any AET will be
			if (a - b != 1 && b - a != 1)
				continue;
			perims += a + b + c;
			cout << a << ' ' << b << ' ' << c << endl;
		}
	}
	cout << perims << endl;
	/*
	const int billion = 1000000000;
	int n = 1, perims = -4;
	for (int m = 1; 2 * m*n*(m + n) <= billion; m++)
	{
		for (n = 1; n <= m; n++)
		{
			if (gcd(m, n) != 1)
				continue;
			for (int k2 = m*m*n / (2 * m + n); k2 < m*n; k2++)
			{
				double ktest = sqrt(k2);
				if (ktest - int(ktest) != 0)
					continue;
				if (gcd(k2, m) != 1 || gcd(k2, n) != 1)
					continue;
				
				//cout << m << ' ' << n << ' ' << k2 << endl;
				int a = n*(m*m + k2);
				int b = m*(n*n + k2);
				int c = (m + n)*(m*n - k2);
				int q = gcd(gcd(a, b), c);
				a /= q, b /= q, c /= q;
				//cout << a << ' ' << b << ' ' << c << endl;
				if ((a == b && abs(a - c) == 1) || (b == c && abs(b - a) == 1) || (c == a && abs(c - b) == 1))
				{
					cout << a << ' ' << b << ' ' << c << endl;
					perims += a + b + c;
				}
			}
		}
	}
	cout << perims << endl;
	//*/
	/*
	const int billion = 1000000000;
	const double epsilon = 0.0000001;
	long long perims = 0;
	LongDouble more, less;
	for (int iso = 3; iso + iso + iso + 1 <= billion; iso++)//2 crashes...
	{
		cout << iso << ' ';
		more = heron(iso, iso, iso + 1, 20);
		less = heron(iso, iso, iso - 1, 20);
		//more.disp();
		//less.disp();
		bool whole = false;
		for (int i = more.exp; i < -1; i++)
			if (more[more.sig.size() + i] == 9)
				whole = true;
			else
			{
				whole = false;
				break;
			}
		if(whole)
			perims += iso + iso + iso + 1;
		whole = false;
		for (int i = more.exp; i < -1; i++)
			if (more[more.sig.size() + i] == 0)
				whole = true;
			else
			{
				whole = false;
				break;
			}
		if (whole)
			perims += iso + iso + iso + 1;
		whole = false;
		for (int i = less.exp; i < -1; i++)
			if (less[less.sig.size() + i] == 9)
				whole = true;
			else
			{
				whole = false;
				break;
			}
		if (whole)
			perims += iso + iso + iso - 1;
		whole = false;
		for (int i = less.exp; i < -1; i++)
			if (less[less.sig.size() + i] == 0)
				whole = true;
			else
			{
				whole = false;
				break;
			}
		if (whole)
			perims += iso + iso + iso - 1;
	}
	cout << '\n' << perims << endl;
	//*/
	
	/*
	const int billion = 1000000000;
	const double epsilon = 0.0000001;
	long long perims = 0;
	double more, less, test;
	cout.precision(15);
	for (int iso = 2; iso + iso + iso + 1 <= 10000000; iso++)
	{
		more = heron(iso, iso, iso + 1);
		less = heron(iso, iso, iso - 1);
		//cout << more << ' ' << less << endl;
		test = fmod(more, 1);
		if (test<epsilon || test - 1>-epsilon)
		{
			perims += iso + iso + iso + 1;
			cout << iso << ' ' << iso << ' ' << iso + 1 << endl;
		}
		test = fmod(less, 1);
		if (test<epsilon || test - 1>-epsilon)
		{
			perims += iso + iso + iso - 1;
			cout << iso << ' ' << iso << ' ' << iso - 1 << endl;
		}
	}
	cout << perims << endl;
	//*/
	/*
	long long perims = 0;
	mpz_t in, out, inner, outer, area2;
	int square;
	for (int iso = 3; iso + iso + iso + 1 <= 1000000000; iso+=2)
	{
		unsigned int s1 = (iso + iso + iso + 1) / 2;
		unsigned int s2 = (iso + iso + iso - 1) / 2;
		unsigned int sab1 = s1 - iso, sab2 = s2 - iso;
		unsigned int sc1 = s1 - iso - 1, sc2 = s2 - iso + 1;
		
		mpz_init(in), mpz_init(out), mpz_init(inner), mpz_init(outer), mpz_init(area2);
		mpz_set_ui(in, sab1), mpz_set_ui(out, s1);
		mpz_mul_ui(inner, in, sab1), mpz_mul_ui(outer, out, sc1);
		mpz_mul(area2, inner, outer);
		//mpz_out_str(stdout, 10, area2), std::cout << '\n';
		square = mpz_perfect_square_p(area2);
		if (square != 0)
		{
			perims += iso + iso + iso + 1;
			std::cout << iso << ' ' << iso << ' ' << iso + 1 << endl;
		}
		mpz_clear(in), mpz_clear(out), mpz_clear(inner), mpz_clear(outer), mpz_clear(area2);
		
		mpz_init(in), mpz_init(out), mpz_init(inner), mpz_init(outer), mpz_init(area2);
		mpz_set_ui(in, sab2), mpz_set_ui(out, s2);
		mpz_mul_ui(inner, in, sab2), mpz_mul_ui(outer, out, sc2);
		mpz_mul(area2, inner, outer);
		//mpz_out_str(stdout, 10, area2), std::cout << '\n';
		square = mpz_perfect_square_p(area2);
		if (square != 0)
		{
			perims += iso + iso + iso - 1;
			std::cout << iso << ' ' << iso << ' ' << iso - 1 << endl;
		}
		mpz_clear(in), mpz_clear(out), mpz_clear(inner), mpz_clear(outer), mpz_clear(area2);
	}
	std::cout << '\n' << perims << endl;
	//*/
	return 0;
}