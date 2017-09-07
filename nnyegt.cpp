#include "connect4.h"

bool strlensort(string a, string b){return (a.length() < b.length());}//sort strings by length

int nnyegt()//replace letters for digits 1-1 in the words in the file and look for square numbers
{//find the largest square that has a square anagram in the file
	vector<string> words;
	ifstream wordfile("words.txt");
	string temp;
	while (getline(wordfile, temp, ','))
		words.push_back(temp.substr(1,temp.length()-2));
	wordfile.close();
	sort(words.begin(), words.end(), strlensort);//sorted by length
	//for (string x : words)
		//cout << x << '\n';
	vector<long long> squares;//create list of squares for later
	for (int n = 1; n < 10000000; n++)
		squares.push_back(long long(n)*n);
	//for (long long x : squares)
		//cout << x << '\n';
	cout << "squared.\n";
	for (int w = 0; w < words.size(); w++)
	{
		for (int w2 = w + 1; w2 < words.size() && words[w2].length() == words[w].length(); w2++)
		{
			if (is_permutation(words[w2].begin(), words[w2].end(), words[w].begin()))//w & w2 anagrams?
			{
				string word = words[w];
				cout << words[w] << ' ' << words[w2] << endl;
		
				for (int s = 0; s < squares.size() && numLength(squares[s]) <= word.length(); s++)//find square for word
				{
					if (numLength(squares[s]) < word.length())
						continue;
					vector<char> subs(10, ' ');//keep track of letter to number substitutions
					vector<short> sqV = itov(squares[s]);
					vector<short> sqV2(sqV.size(), 0);
					for (int let = 0; let < word.length(); let++)
					{
						for (int c = 0; c < subs.size(); c++)//create letter to digit map and make sure they're 1-1
							if (word[let] == subs[c] && sqV[let] != c || subs[c] != ' ' && word[let] != subs[c] && sqV[let] == c)
								goto NewSquare;
						subs[sqV[let]] = word[let];//
					}
					for (int d = 0; d < sqV2.size(); d++)
					{
						char cur = words[w2][d];//make same replacements with word2
						for (int s = 0; s < subs.size(); s++)
							if (subs[s] == cur)
								sqV2[d] = s;
					}
					if (sqV2[0] == 0)
						continue;
					long long square = vtoi(sqV);
					long long square2 = vtoi(sqV2);
					if (binary_search(squares.begin(), squares.end(), square2))//check if word2 is a square
						cout << ' ' << square << ' ' << square2 << endl;
				NewSquare:;
				}
			}
		}
	}


	return 0;
}