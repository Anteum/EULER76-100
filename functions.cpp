#include "connect4.h"
#include "classes.h"

//function definitions here
long long vSum(vector<short> nums)
{
	long long sum = 0;
	for (int i = 0; i < nums.size(); i++)
		sum += nums[i];
	return sum;
}

template<typename T>
void vPrint(vector<T> digits)
{
	for (int ind = 0; ind < digits.size(); ind++)
		cout << digits[ind] << ' ';
	cout << endl;
}
template void vPrint(vector<short> digits);
template void vPrint(vector<long long> digits);

bool isPrime(long long n)
{
	if (n == 1)
		return false;
	if (n == 2 || n == 3 || n == 5 || n == 7)
		return true;
	if (n % 2 == 0)
		return false;
	if (n % 3 == 0)
		return false;
	if (n % 5 == 0)
		return false;
	if (n % 7 == 0)
		return false;
	for (int i = 11; i < n / 10; i += 2)
		if (n%i == 0)
			return false;
	return true;
}

int numLength(long long i)
{
	int n = 1;
	while (i >= 10)
	{
		n++;
		i /= 10;
	}
	return n;
}

vector<short> itov(long long n)
{
	vector<short> digits;
	int length = numLength(n);
	long long order = 1;
	for (int i = 1; i < length; i++)
		order *= 10;
	for (; order >= 1; order /= 10)
	{
		digits.push_back(n / order);
		while (n >= order)
			n -= order;
	}
	return digits;
}

long long vtoi(vector<short> nVector)
{
	long long number = 0, place = 1;
	for (int i = nVector.size() - 1; i >= 0; i--)
	{
		number += nVector[i] * place;
		place *= 10;
	}
	return number;
}

vector<short> vecPlus(vector<short> vec)
{
	vec.back()++;
	for (int i = vec.size() - 1; i > 0; i--)
	{
		if (vec[i] == 10)
		{
			vec[i - 1]++;
			vec[i] = 0;
		}
	}
	if (vec[0] == 10)
	{
		vec[0] = 0;
		vec.insert(vec.begin(), 1);
	}
	return vec;
}

bool vIsGreater(vector<short> a, vector<short> b)//a is greater than or equal to b
{
	for (int i = 0; i < a.size() - 1; i++)//remove leading 0's from a
	{
		if (a[i] == 0)
			pop_front(a);
		else
			break;
	}
	for (int i = 0; i < b.size() - 1; i++)//remove leading 0's from b
	{
		if (b[i] == 0)
			pop_front(b);
		else
			break;
	}
	if (a.size() > b.size())
		return true;
	else if (b.size() > a.size())
		return false;
	else
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] > b[i])
				return true;
			else if (b[i] > a[i])
				return false;
		}
	return false;//this determines if a is greater when a == b; true for yes, false for no
}

vector<short> diffVecs(vector<short> minu, vector<short> subtrah)
{
	vector<short> diff;//create reversed
	bool neg = false;
	if (vIsGreater(subtrah, minu))
	{
		neg = true;
		swap(subtrah, minu);
	}
	for (int i = 1; i <= min(subtrah.size(), minu.size()); i++)
	{
		if (minu[minu.size() - i] - subtrah[subtrah.size() - i] >= 0)
			diff.push_back(minu[minu.size() - i] - subtrah[subtrah.size() - i]);
		else
		{
			for (int j = minu.size() - i - 1; j >= 0; j--)
			{
				if (minu[j] != 0)
				{
					minu[j]--;
					minu[j + 1] += 10;
					i--;
					break;
				}
			}
		}
	}
	for (int i = subtrah.size() + 1; i <= minu.size(); i++)
		diff.push_back(minu[minu.size() - i]);
	while (diff.back() == 0 && diff.size() > 1)
		diff.pop_back();
	reverse(diff.begin(), diff.end());
	if (neg)
		diff[0] *= -1;
	return diff;
}

vector<short> divVecAndDig(vector<short> dend, short sor)
{
	vector<short> quot;
	for (int i = 0; i < dend.size(); i++)
	{
		if (dend[i] >= sor)
		{
			quot.push_back(dend[i] / sor);
			dend[i] %= sor;
		}
		else if (quot.size() > 0)
			quot.push_back(0);
		if (i < dend.size() - 1)
			dend[i + 1] += dend[i] * 10;
		dend[i] = 0;
	}
	return quot;
}

vector<short> multVecAndInt(vector<short> cand, int er)
{
	vector<short> product;
	int bonus = 0;
	for (int ind = cand.size() - 1; ind >= 0; ind--)
	{
		bonus += (cand[ind] * er);
		product.push_back(bonus % 10);
		bonus /= 10;
	}
	while (bonus>0)
	{
		product.push_back(bonus % 10);
		bonus /= 10;
	}
	vector<short> reverse;
	for (int i = product.size() - 1; i >= 0; i--)
		reverse.push_back(product[i]);
	return reverse;
	//create product reversed and reverse right before return
}

vector<short> multVecs(vector<short> cand, vector<short> er)//create return vector backwards
{
	vector<short> prod(cand.size() + er.size(), 0);//to be reversed then returned
	vector<short> revprod;
	for (int j = er.size() - 1; j >= 0; j--)
	{
		int place = 0 + er.size() - 1 - j;
		for (int i = cand.size() - 1; i >= 0; i--)
		{
			prod[place] += (cand[i] * er[j]) % 10;
			if (prod[place] > 9)
			{
				prod[place] -= 10;
				prod[place + 1]++;
			}
			prod[place + 1] += (cand[i] * er[j]) / 10;
			//prod.push_back(0);
			if (prod[place + 1] > 9)
			{
				prod[place + 1] -= 10;
				prod[place + 2]++;
			}
			place++;
		}
	}
	for (int i = prod.size() - 1; i >= 0; i--)//time to reverse product
	{
		if (i == prod.size() - 1 && prod[i] == 0)//and remove possible leading zero
			i--;
		revprod.push_back(prod[i]);
	}
	return revprod;
}

void pop_front(vector<short>& mutiny)//take element off front of vector (&delete)
{
	for (int i = 0; i<(mutiny.size() - 1); i++)
	{
		mutiny[i] = mutiny[i + 1];
	}
	mutiny.pop_back();//mutiny.resize(mutiny.size() - 1);
}

vector<short> sumVecs(vector <short> and1, vector<short> and2)
{//assume and1 >~ and2
	if (and2.size() > and1.size())
		swap(and1, and2);
	vector<short> sum(and1);
	sum.insert(sum.begin(), 0);
	for (int i = 1; i <= and2.size(); i++)
		sum[sum.size() - i] += and2[and2.size() - i];
	for (int i = 1; i <= sum.size(); i++)
	{
		if (sum[sum.size() - i] >= 10)
		{
			sum[sum.size() - i] -= 10;
			sum[sum.size() - (i + 1)]++;
		}
	}
	if (sum[0] == 0)
		pop_front(sum);
	return sum;
}

long long partitionsP(long long n)//includes 'n' as a partition of n
{//formula by Euler...slow..but not with memoization!
	static vector<long long> memo(1000000, 0);//static lets memo retain its state as function recurses
	long long total = 0;
	if (n == 0 || n == 1)
		return 1;
	if (n < 0)
		return 0;
	if (memo[n] != 0)
		return memo[n];
	for (long long k = 1; k <= n; k++)
	{
		long long temp = partitionsP(n - k*(3 * k - 1) / 2) + partitionsP(n - k*(3 * k + 1) / 2);
		if (k % 2 == 1)
			total += temp;
		else
			total -= temp;
	}
	memo[n] = total;
	return total;
}
//*
vector<short> partitionsPV(vector<short> nVec)
{
	static vector<vector<short>> memo(100000, vector<short>(1, 0));
	vector<short> total(1, 0);
	if (nVec == itov(0) || nVec == itov(1))
		return itov(1);
	if (nVec[0] < 0)
		return itov(0);
	if (memo[vtoi(nVec)] != itov(0))//
		return memo[vtoi(nVec)];
	for (vector<short> kVec = itov(1); !vIsGreater(kVec, nVec); kVec = vecPlus(kVec))
	{
		vector<short> temp = partitionsPV(diffVecs(nVec, divVecAndDig(multVecs(kVec, diffVecs(multVecs(itov(3), kVec), itov(1))), 2)));
		temp = sumVecs(temp, partitionsPV(diffVecs(nVec, divVecAndDig(multVecs(kVec, vecPlus(multVecs(itov(3), kVec))), 2))));
		if (kVec.back() % 2 == 1)
			total = sumVecs(total, temp);
		else
			total = diffVecs(total, temp);
	}
	memo[vtoi(nVec)] = total;
	return total;
}
//*/
long long partitionsPmod(long long n, long long mod)//includes 'n' as a partition of n
{
	static vector<long long> memo(1000000, 0);//static lets memo retain its state as function recurses
	long long total = 0;
	if (n == 0 || n == 1)
		return 1;
	if (n < 0)
		return 0;
	if (memo[n] != 0)
		return memo[n];
	for (long long k = 1; k <= n; k++)
	{
		long long temp = partitionsPmod(n - k*(3 * k - 1) / 2, mod) + partitionsPmod(n - k*(3 * k + 1) / 2, mod);
		if (k % 2 == 1)
			total += temp;
		else
			total -= temp;
		total %= mod;
	}
	memo[n] = total;
	return total;
}

vector<short> preciSqrt(int n, int precision)
{
	vector<short> root, nVec = itov(n), cur, left;
	int x, ind = 0;
	cur.push_back(nVec[ind]);
	ind++;
	if (nVec.size() % 2 == 0)
	{ 
		cur.push_back(nVec[ind]);
		ind++;
	}
	for (int d = 1; d <= precision * 2 + 2; d++)//?
		nVec.push_back(0);
	
	for (x = 1; (x + 1)*(x + 1) <= vtoi(cur); x++)
	{}
	root.push_back(x);
	left = itov(2 * x);
	cur = itov(vtoi(cur) - x*x);
	while (ind < nVec.size() - 2)
	{
		cur.push_back(nVec[ind++]);
		cur.push_back(nVec[ind++]);
		/*
		for (int i = 0; i < cur.size() - 1; i++)//remove leading 0's from cur
		{
			if (cur[i] == 0)
				pop_front(cur);
			else
				break;
		}
		//*///taught vIsGreater and diffVecs about leading 0's instead
		left.push_back(-1);
		for (int d = 1; d <= 10; d++)
		{
			left.back()++;
			if (vIsGreater(multVecs(vecPlus(left), itov(d)), cur))
			{
				root.push_back(d - 1);
				cur = diffVecs(cur, multVecs(left, itov(d - 1)));
				left = multVecs(root, itov(2));
				break;
			}
		}
	}
	return root;
}

template<typename T>
vector<T> primeFactors(T n)
{
	vector<T> factors;
	for (int x = 2; x <= sqrt(n); x++)
	{
		if (n%x == 0)
		{
			factors.push_back(x);
			n /= x;
			x--;
		}
		if (x + 1 > sqrt(n))
		{
			factors.push_back(n);
			return factors;
		}
	}
	if (n > 1)
		factors.push_back(n);
	return factors;
}
template vector<short> primeFactors(short n);
template vector<int> primeFactors(int n);
template vector<long long> primeFactors(long long n);

vector<short> uniqEle(vector<short> eles)
{
	vector<short> uniques;
	uniques.push_back(eles[0]);
	for (int n = 1; n < eles.size(); n++)
	{
		for (int i = 0; i < uniques.size(); i++)
		{
			if (eles[n] == uniques[i])
				goto NextN;
		}
		uniques.push_back(eles[n]);
	NextN:;
	}
	return uniques;
}

int gcd(int a, int b)//euclidean algorithm with modulo
{
	while (b > 0)
	{
		int temp = b;
		b = a%b;
		a = temp;
	}
	return a;
}



long long dijkstraPath(GridGraph g, int ya, int xa, int yb, int xb)
{
	NodeList adjNodes, candNodes;//adjNodes is list of adjacent nodes to current and candNodes is nodes that could work for path
	WeightedNode goal = g.grid[yb][xb], cur;
	candNodes.pushNode(g.grid[ya][xa]);
	candNodes.nList.back().pathSum = candNodes.nList.back().weight;//pay up front to start journey
	while (candNodes.nList.size() > 0)
	{
		cur = candNodes.nList.back();//move last element from candNodes list to current node
		candNodes.nList.pop_back();
		if (g.grid[goal.y][goal.x].visited)//check if destination node has been current before
			break;
		if (cur.u)//if possible, put adjacents in adjNodes
			adjNodes.nList.push_back(g.grid[cur.y - 1][cur.x]);
		if (cur.r)
			adjNodes.nList.push_back(g.grid[cur.y][cur.x + 1]);
		if (cur.d)
			adjNodes.nList.push_back(g.grid[cur.y + 1][cur.x]);
		if (cur.l)
			adjNodes.nList.push_back(g.grid[cur.y][cur.x - 1]);
		for (WeightedNode n : adjNodes.nList)
		{
			if (n.visited)//don't bother with nodes that have been current before
				continue;
			long long pathWeight = cur.pathSum + n.weight;
			if (pathWeight < n.pathSum)//if the path sum to and including node is less than before (is initially infinity)
			{
				g.grid[n.y][n.x].pathSum = pathWeight;//update path sum to node
				candNodes.pushNode(g.grid[n.y][n.x]);//add node to candNodes list
			}
		}
		adjNodes.nList.clear();
		g.grid[cur.y][cur.x].visited = true;//set node to not become current again
	}
	return g.grid[goal.y][goal.x].pathSum;//
}

