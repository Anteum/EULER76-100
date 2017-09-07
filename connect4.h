#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;
//declare classes
class WeightedNode;
class GridGraph;
class NodeList;

//declare functions here
long long vSum(vector<short>);//sum of numbers in elements of vector
template<typename T>
	void vPrint(vector<T>);//prints vectors of shorts
bool isPrime(long long);//returns primality of n > 0
int numLength(long long);//returns number of digits in int > 0	
vector<short> itov(long long);//returns a vector of the digits of input
long long vtoi(vector<short>);//counterpart to itov()
vector<short> vecPlus(vector<short>);//add 1 to vectorized number
bool vIsGreater(vector<short>, vector<short>);//is first vector > to second
vector<short> diffVecs(vector<short>, vector<short>);//first vec minus second
vector<short> divVecAndDig(vector<short>, short);//return quotient of vector and single digit (remainder is discarded)
vector<short> multVecAndInt(vector<short>,int);//returns product of vector multiplicand and int multiplier
vector<short> multVecs(vector<short>, vector<short>);//multiply vectors as numbers
void pop_front(vector<short>&);//delete first element from vector of shorts
vector<short> sumVecs(vector<short>, vector<short>);//sum vectors as numbers
long long partitionsP(long long);//gives number of unique "partitions" of n  (includes 'n' as a partition of n)
vector<short> partitionsPV(vector<short>);//vector version of above
long long partitionsPmod(long long, long long);//third time is charm?
vector<short> preciSqrt(int, int);//second parameter is # of digits after decimal returned
template<typename T>
	vector<T> primeFactors(T);//returns vector of factors (short int version)
vector<short> uniqEle(vector<short>);//returns list of unique elements from input
int gcd(int, int);

long long dijkstraPath(GridGraph, int, int, int, int);//ints are start row,start col,end row,end col

int svysix();
int svysvn();
int svyegt();
int svynin();
int eghty();
int egyone();
int egytwo();
int egythr();
int egyfor();
int egyfiv();
int egysix();
int egysvn();
int egyegt();
int egynin();
int ninty();
int nnyone();
int nnytwo();
int nnythr();
int nnyfor();
int nnyfiv();
int nnysix();
int nnysvn();
int nnyegt();
int nnynin();
int hundrd();


