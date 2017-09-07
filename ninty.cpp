#include "connect4.h"

bool dispsSqs(vector<bool> v1, vector<bool> v2)
{
	if (v1[0] && v2[1] || v1[1] && v2[0])//1 is displayable
	{
		if (v1[0] && v2[4] || v1[4] && v2[0])//4
		{
			if (v1[0] && (v2[9] || v2[6]) || (v1[9] || v1[6]) && v2[0])//9
			{
				if (v1[1] && (v2[6] || v2[9]) || (v1[6] || v1[9]) && v2[1])//16
				{
					if (v1[2] && v2[5] || v1[5] && v2[2])//25
					{
						if (v1[3] && (v2[6] || v2[9]) || (v1[6] || v1[9]) && v2[3])//36
						{
							if (v1[4] && (v2[9] || v2[6]) || (v1[9] || v1[6]) && v2[4])//49
							{
								if ((v1[6] || v1[9]) && v2[4] || v1[4] && (v2[6] || v2[9]))//64
								{
									if (v1[8] && v2[1] || v1[1] && v2[8])//81
									{
										return true;//all are displayable
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int ninty()//create 2 dice, each out of unique digits 0 to 9 and try to form square numbers when placed side-by-side
{//let an upside-down 6 be a 9 and vice-versa; find the amount of digit combinations for the dice can form 1,4,...81
	long long arrangs = 0;
	for (short a = 0; a <= 4; a++)//die 1, side 1
	{
		for (short b = a + 1; b <= 5; b++)
		{
			for (short c = b + 1; c <= 6; c++)
			{
				for (short d = c + 1; d <= 7; d++)
				{
					for (short e = d + 1; e <= 8; e++)
					{
						for (short f = e + 1; f <= 9; f++)//die 1, side 6
						{
							vector<bool> d1(10, false);//bool vector where digits appearing on die 1 are true
							d1[a] = true, d1[b] = true, d1[c] = true, d1[d] = true, d1[e] = true, d1[f] = true;
							for (short u = 0; u <= 4; u++)//die 2, side 1
							{
								for (short v = u + 1; v <= 5; v++)
								{
									for (short w = v + 1; w <= 6; w++)
									{
										for (short x = w + 1; x <= 7; x++)
										{
											for (short y = x + 1; y <= 8; y++)
											{
												for (short z = y + 1; z <= 9; z++)//die 2, side 6
												{
													vector<bool> d2(10, false);//bool vector where digits appearing on die 2 are true
													d2[u] = true, d2[v] = true, d2[w] = true, d2[x] = true, d2[y] = true, d2[z] = true;
													if (dispsSqs(d1, d2))//check if all squares are displayable by current dice
														arrangs++;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << arrangs / 2 << endl;//dice's arrangements also work switched so working arrangements were counted twice

	return 0;
}