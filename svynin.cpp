#include "connect4.h"

bool keyInCode(string code, string key)//checks if digits of key are within code in same relative order
{
	int k = 0;
	for (int d = 0; d < code.length(); d++)
	{
		if (key[k] == code[d])
		{
			if (k == key.length() - 1)
				return true;
			k++;
		}
	}
	return false;
}

int svynin()//find the shortest "code" that contains all the numbers (in the same relative order) of each of the "keys" in the file
{
	vector<string> keys;
	ifstream log("keylog.txt");
	string temp;
	while (getline(log, temp))
		keys.push_back(temp);
	log.close();
	string code = keys[0];//start code out as first key
	char a, b;
	while (true)
	{
		for (int d = 0; d < code.length() - 1; d++)//cycle thru current code
		{
			a = code[d], b = code[d + 1];//have a & b be adjacent digits in the code
			for (int k = 0; k < keys.size(); k++)//for each key from the file
			{
				if (keys[k][0] == a && keys[k][2] == b)//if the 1st and 3rd digits of key match a & b respectively, insert key's 2nd digit between a & b
				{
					code.insert(code.begin() + d + 1, keys[k][1]);
					goto NextRound;
				}
				else if (d == 0 && keys[k][1] == a && keys[k][2] == b)//if the 2nd and 3rd digits of key match a & b, insert key's 1st digit in front
				{
					code.insert(code.begin(), keys[k][0]);
					goto NextRound;
				}
				else if (d == code.length() - 2 && keys[k][0] == a && keys[k][1] == b)//if the 1st and 2nd digits of key match a & b, insert key's 3rd digit in back
				{
					code.push_back(keys[k][2]);
					goto NextRound;
				}
			}
		}
		for (int k = 0; k < keys.size(); k++)//check if all keys exist in code
			if (!keyInCode(code, keys[k]))
				goto NextRound;
		break;//if all keys in code, done
	NextRound:;
	}
	cout << code << endl;
	return 0;
}