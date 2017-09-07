#include "connect4.h"

int egynin()//write all the numbers displayed in roman numerals in the file using the minimal amount of roman numerals
{//find the number of characters saved by doing this
	vector<string> romNums, minRoms;
	ifstream romStream("roman.txt");
	string temp;
	while (getline(romStream, temp))
		romNums.push_back(temp);
	romStream.close();
	int charTotal = 0, minTotal = 0;
	for (string romInt : romNums)
		charTotal += romInt.length();//starting number of characters
	vector<int> arabicNums;
	for (int i = 0; i < romNums.size(); i++)//convert each number in roman numerals into arabic numerals
	{
		int arabic = 0;
		for (int c = 0; c < romNums[i].length(); c++)
		{
			switch (romNums[i][c])
			{
			case 'I':	arabic += 1;
				break;
			case 'V':	arabic += 5;
				break;
			case 'X':	arabic += 10;
				break;
			case 'L':	arabic += 50;
				break;
			case 'C':	arabic += 100;
				break;
			case 'D':	arabic += 500;
				break;
			case 'M':	arabic += 1000;
				break;
			default: //nothing
				break;
			}
		}
		for (int cc = 0; cc < romNums[i].length() - 1; cc++)//deduct amounts overcounted by ignoring subtractive notation
		{
			string pair = romNums[i].substr(cc, 2);
			if (pair == "IV" || pair == "IX")
				arabic -= 2;
			else if (pair == "XL" || pair == "XC")
				arabic -= 20;
			else if (pair == "CD" || pair == "CM")
				arabic -= 200;
		}
		arabicNums.push_back(arabic);
	}
	for (int n = 0; n < arabicNums.size(); n++)//convert each number in arabic numerals to minimized roman numerals
	{
		vector<short> araVec = itov(arabicNums[n]);
		reverse(araVec.begin(), araVec.end());//reversed for ease-of-use below
		string minRom = "";
		if (araVec.size() == 4)
			for (int m = 1; m <= araVec[3]; m++)
				minRom.push_back('M');
		if (araVec.size() >= 3)
		{
			if (araVec[2] == 9)
			{
				minRom.push_back('C');
				minRom.push_back('M');
			}
			else if (araVec[2] >= 5)
			{
				minRom.push_back('D');
				for (int c = 1; c <= araVec[2] - 5; c++)
					minRom.push_back('C');
			}
			else if (araVec[2] == 4)
			{
				minRom.push_back('C');
				minRom.push_back('D');
			}
			else
			{
				for (int c = 1; c <= araVec[2]; c++)
					minRom.push_back('C');
			}
		}
		if (araVec.size() >= 2)
		{
			if (araVec[1] == 9)
			{
				minRom.push_back('X');
				minRom.push_back('C');
			}
			else if (araVec[1] >= 5)
			{
				minRom.push_back('L');
				for (int x = 1; x <= araVec[1] - 5; x++)
					minRom.push_back('X');
			}
			else if (araVec[1] == 4)
			{
				minRom.push_back('X');
				minRom.push_back('L');
			}
			else
			{
				for (int x = 1; x <= araVec[1]; x++)
					minRom.push_back('X');
			}
		}
		if (araVec.size() >= 1)
		{
			if (araVec[0] == 9)
			{
				minRom.push_back('I');
				minRom.push_back('X');
			}
			else if (araVec[0] >= 5)
			{
				minRom.push_back('V');
				for (int i = 1; i <= araVec[0] - 5; i++)
					minRom.push_back('I');
			}
			else if (araVec[0] == 4)
			{
				minRom.push_back('I');
				minRom.push_back('V');
			}
			else
			{
				for (int i = 1; i <= araVec[0]; i++)
					minRom.push_back('I');
			}
		}
		minRoms.push_back(minRom);
	}
	//for (int i = 0; i < romNums.size(); i++)
		//cout << romNums[i] << '\t' << arabicNums[i] << '\t' << minRoms[i] << endl;
	for (string min : minRoms)
		minTotal += min.length();//new number of characters
	cout << charTotal - minTotal << endl;

	return 0;
}