#include "connect4.h"

class Doku//simple sudoku element container
{
public:
	short val;
	short box;
};

bool correct(vector<vector<Doku>> const grid)//verify sudoku solutions
{
	vector<vector<short>> rowx(9, vector<short>(10, 0));
	vector<vector<short>> colx(9, vector<short>(10, 0));
	vector<vector<short>> boxx(10, vector<short>(10, 0));
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			rowx[row][grid[row][col].val]++;
			colx[col][grid[row][col].val]++;
			boxx[grid[row][col].box][grid[row][col].val]++;
		}
	}
	for (int row = 0; row < 9; row++)
	{
		for (int col = 1; col <= 9; col++)
		{
			if (rowx[row][col] != 1)
				return false;
			if (colx[row][col] != 1)
				return false;
		}
	}
	for (int row = 1; row <= 9; row++)
	{
		for (int col = 1; col <= 9; col++)
		{
			if (boxx[row][col] != 1)
				return false;
		}
	}
	return true;
}

bool full(vector<vector<Doku>> const grid)//quickly check if puzzle is done
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (grid[row][col].val == 0)
				return false;
		}
	}
	return true;
}

vector<vector<Doku>> sudoku(vector<vector<Doku>> grid)//sudoku solver
{//use only basic candidate techniques and guess and check from there
	vector<vector<vector<bool>>> candGrid(10, vector<vector<bool>>(9, vector<bool>(9, true)));
	vector<short> candList(10,0);
	bool easy;
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			if (grid[row][col].val != 0)//set initial candidates
			{//candidates are numbers that are able to be in a particular free spot
				for (int d = 1; d <= 9; d++)
					candGrid[d][row][col] = false;
				for (int row2 = 0; row2 < 9; row2++)
					for (int col2 = 0; col2 < 9; col2++)
						if (row == row2 || col == col2 || grid[row][col].box == grid[row2][col2].box)
							candGrid[grid[row][col].val][row2][col2] = false;
			}
	for (;;)//ever
	{
		if (full(grid))
			return grid;
		easy = false;
		for (int row = 0; row < 9; row++)//if an element has a single candidate make it that number
			for (int col = 0; col < 9; col++)
				if (grid[row][col].val == 0)
				{
					int cands = 0;
					for (int d = 1; d <= 9; d++)
						if (candGrid[d][row][col])
							cands++;
					if (cands == 1)
						for (int d = 1; d <= 9; d++)
							if (candGrid[d][row][col])
							{
								grid[row][col].val = d;
								for (int row2 = 0; row2 < 9; row2++)
									for (int col2 = 0; col2 < 9; col2++)
										if (row == row2 || col == col2 || grid[row][col].box == grid[row2][col2].box)
											candGrid[d][row2][col2] = false;
								easy = true;
							}
				}
		//*
		for (int row = 0; row < 9; row++)//if a digit is a candidate in a row only once make its element that digit
		{
			candList = vector<short>(10, 0);
			for (int col = 0; col < 9; col++)
				if (grid[row][col].val == 0)
					for (int d = 1; d <= 9; d++)
						if (candGrid[d][row][col])
							candList[d]++;
			for (int d = 1; d <= 9; d++)
				if (candList[d] == 1)
					for (int col = 0; col < 9; col++)
						if (candGrid[d][row][col])
						{
							grid[row][col].val = d;
							for (int row2 = 0; row2 < 9; row2++)
								for (int col2 = 0; col2 < 9; col2++)
								{
									if (row == row2 || col == col2 || grid[row][col].box == grid[row2][col2].box)
										candGrid[d][row2][col2] = false;
									if (row == row2 && col == col2)
										for (int d2 = 1; d2 <= 9; d2++)
											candGrid[d2][row][col] = false;
								}
							easy = true;
						}
		}
		for (int col = 0; col < 9; col++)//if a digit is a candidate in a column only once make its element that digit
		{
			candList = vector<short>(10, 0);
			for (int row = 0; row < 9; row++)
				if (grid[row][col].val == 0)
					for (int d = 1; d <= 9; d++)
						if (candGrid[d][row][col])
							candList[d]++;
			for (int d = 1; d <= 9; d++)
				if (candList[d] == 1)
					for (int row = 0; row < 9; row++)
						if (candGrid[d][row][col])
						{
							grid[row][col].val = d;
							for (int row2 = 0; row2 < 9; row2++)
								for (int col2 = 0; col2 < 9; col2++)
								{
									if (row == row2 || col == col2 || grid[row][col].box == grid[row2][col2].box)
										candGrid[d][row2][col2] = false;
									if (row == row2 && col == col2)
										for (int d2 = 1; d2 <= 9; d2++)
											candGrid[d2][row][col] = false;
								}
							easy = true;
						}
		}
		if (easy == false)//if basic strategies don't cut it
		{
			cout << '.';
			vector<vector<Doku>> gridA, gridB, gridA2, gridB2;
			bool first;
			for (int row = 0; row < 9; row++)//if an element has only 2 candidates, try each one with recursion
				for (int col = 0; col < 9; col++)
				{
					gridA = grid, gridB = grid;
					if (grid[row][col].val == 0)
					{
						int cands = 0;
						for (int d = 1; d <= 9; d++)
							if (candGrid[d][row][col])
								cands++;
						if (cands == 2)
						{
							first = true;
							for (int d = 1; d <= 9; d++)
							{
								if (candGrid[d][row][col] && first)
								{
									gridA[row][col].val = d;
									gridA2 = sudoku(gridA);
									if (full(gridA2))
										return gridA2;
									gridA[row][col].val = 0;
									first = false;
								}
								if (candGrid[d][row][col] && !first)
								{
									gridB[row][col].val = d;
									gridB2 = sudoku(gridB);
									if (full(gridB2))
										return gridB2;
									gridB[row][col].val = 0;
									for (int row2 = 0; row2 < 9; row2++)
										for (int col2 = 0; col2 < 9; col2++)
											if (gridA2[row2][col2].val == gridB2[row2][col2].val && grid[row2][col2].val == 0)
											{
												grid[row2][col2].val = gridA2[row2][col2].val;
												/*//somehow is worse?
												for (int row3 = 0; row3 < 9; row3++)
													for (int col3 = 0; col3 < 9; col3++)
													{
														if (row3 == row2 || col3 == col2 || grid[row3][col3].box == grid[row2][col2].box)
															candGrid[grid[row2][col2].val][row3][col3] = false;
														if (row3 == row2 && col3 == col2)
															for (int d2 = 1; d2 <= 9; d2++)
																candGrid[d2][row3][col3] = false;
													}
												//*/
											}
								}
							}
						}
					}
				}
			break;
		}
	}
	return grid;
}

/*
vector<vector<Doku>> sudoku(vector<vector<Doku>> grid)//7,46,48,49 fail...
{
	bool done = false, easy = true, expert = false;
	vector<short> boxes(10, 0);
	vector<short> rows(9, 0);
	vector<short> cols(9, 0);
	vector<vector<Doku>> grid2;
	vector<vector<vector<bool>>> candGrid(10, vector<vector<bool>>(9, vector<bool>(9, true)));
	while (!done)
	{
		if (full(grid))
			return grid;
		easy = false;//?
		//*
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (grid[row][col].val != 0)
				{
					for (int d = 1; d <= 9; d++)
						if (grid[row][col].val != d)//maybe comment this line
							candGrid[row][col][d] = false;
					for (int row2 = 0; row2 < 9; row2++)
					{
						for (int col2; col2 < 9; col2++)
						{
							if (!(row == row2 && col == col2))
								if (row == row2 || col == col2 || grid[row][col].box == grid[row2][col2].box)
									candGrid[row2][col2][grid[row][col].val] = false;

						}
					}
				}
			}
		}
		//*
		//*
		for (int d = 1; d <= 9; d++)
		{
			grid2 = grid;
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					if (grid2[row][col].val == d)
					{
						for (int row2 = 0; row2 < 9; row2++)
						{
							for (int col2 = 0; col2 < 9; col2++)
							{
								if (row2 == row && grid2[row2][col2].val == 0)
									grid2[row2][col2].val = -1;
								if (col2 == col && grid2[row2][col2].val == 0)
									grid2[row2][col2].val = -1;
								if (grid2[row2][col2].box == grid2[row][col].box && grid2[row2][col2].val == 0)
									grid2[row2][col2].val = -1;
							}
						}
					}
				}
			}
			boxes = vector<short>(10, 0);
			rows = vector<short>(9, 0);
			cols = vector<short>(9, 0);
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					if (grid2[row][col].val == 0)
					{
						rows[row]++;
						cols[col]++;
						boxes[grid2[row][col].box]++;
					}
				}
			}
			for (int b = 1; b < 10; b++)
				if (boxes[b] == 1)
					for (int row = 0; row < 9; row++)
						for (int col = 0; col < 9; col++)
							if (grid2[row][col].val == 0 && grid2[row][col].box == b)
								grid[row][col].val = d, easy = true;
			for (int r = 1; r < 9; r++)
				if (rows[r] == 1)
					for (int col = 0; col < 9; col++)
						if (grid2[r][col].val == 0)
							grid[r][col].val = d, easy = true;
			for (int c = 1; c < 9; c++)
				if (cols[c] == 1)
					for (int row = 0; row < 9; row++)
						if (grid2[row][c].val == 0)
							grid[row][c].val = d, easy = true;
		}
		//*
		if (easy == false)////////////////////////////////////////////////////////////
		{
			//break;
			cout << 'm' << ' ';
			vector<vector<Doku>> gridA, gridB, gridA2, gridB2;
			for (int d = 1; d <= 9; d++)
			{
				gridA = grid, gridB = grid;
				bool first;
				///
				grid2 = grid;
				for (int row = 0; row < 9; row++)
				{
					for (int col = 0; col < 9; col++)
					{
						if (grid2[row][col].val == d)
						{
							for (int row2 = 0; row2 < 9; row2++)
							{
								for (int col2 = 0; col2 < 9; col2++)
								{
									if (row2 == row && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
									if (col2 == col && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
									if (grid2[row2][col2].box == grid2[row][col].box && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
								}
							}
						}
					}
				}
				boxes = vector<short>(10, 0);
				rows = vector<short>(9, 0);
				cols = vector<short>(9, 0);
				for (int row = 0; row < 9; row++)
				{
					for (int col = 0; col < 9; col++)
					{
						if (grid2[row][col].val == 0)
						{
							rows[row]++;
							cols[col]++;
							boxes[grid2[row][col].box]++;
						}
					}
				}
				///
				for (int b = 1; b < 10; b++)
				{
					if (boxes[b] == 2)
					{
						first = true;
						for (int row = 0; row < 9; row++)
						{
							for (int col = 0; col < 9; col++)
							{
								if (grid2[row][col].val == 0 && grid2[row][col].box == b && first)
								{
									gridA[row][col].val = d;
									gridA2 = sudoku(gridA);
									if (full(gridA2))
										return gridA2;
									gridA[row][col].val = 0;
									first = false;
								}
								if (grid2[row][col].val == 0 && grid2[row][col].box == b && !first)
								{
									gridB[row][col].val = d;
									gridB2 = sudoku(gridB);
									if (full(gridB2))
										return gridB2;
									gridB[row][col].val = 0;
								}
								/*
								if(!first)
									for (int row2 = 0; row2 < 9; row2++)
										for (int col2 = 0; col2 < 9; col2++)
											if (gridA2[row2][col2].val == gridB2[row2][col2].val)
												grid[row2][col2].val = gridA2[row2][col2].val;
							//*
							}
						}
					}
				}
				for (int r = 0; r < 9; r++)
				{
					if (rows[r] == 2)
					{
						first = true;
						for (int col = 0; col < 9; col++)
						{
							if (grid2[r][col].val == 0 && first)
							{
								gridA[r][col].val = d;
								gridA2 = sudoku(gridA);
								if (full(gridA2))
									return gridA2;
								gridA[r][col].val = 0;
								first = false;
							}
							if (grid2[r][col].val == 0 && !first)
							{
								gridB[r][col].val = d;
								gridB2 = sudoku(gridB);
								if (full(gridB2))
									return gridB2;
								gridB[r][col].val = 0;
							}
							/*
							if (!first)
								for (int row2 = 0; row2 < 9; row2++)
									for (int col2 = 0; col2 < 9; col2++)
										if (gridA2[row2][col2].val == gridB2[row2][col2].val)
											grid[row2][col2].val = gridA2[row2][col2].val;
							//*
						}
					}
				}
				for (int c = 0; c < 9; c++)
				{
					if (cols[c] == 2)
					{
						first = true;
						for (int row = 0; row < 9; row++)
						{
							if (grid2[row][c].val == 0 && first)
							{
								gridA[row][c].val = d;
								gridA2 = sudoku(gridA);
								if (full(gridA2))
									return gridA2;
								gridA[row][c].val = 0;
								first = false;
							}
							if (grid2[row][c].val == 0 && !first)
							{
								gridB[row][c].val = d;
								gridB2 = sudoku(gridB);
								if (full(gridB2))
									return gridB2;
								gridB[row][c].val = 0;
							}
							/*
							if (!first)
								for (int row2 = 0; row2 < 9; row2++)
									for (int col2 = 0; col2 < 9; col2++)
										if (gridA2[row2][col2].val == gridB2[row2][col2].val)
											grid[row2][col2].val = gridA2[row2][col2].val;
							//*
						}
					}
				}
			}
			expert = true;
		}
		if (expert)
		{
			/*
			cout << 'e' << ' ';
			///
			vector<vector<Doku>> gridA, gridB, gridA2, gridB2, gridC, gridC2;
			for (int d = 1; d <= 9; d++)
			{
				gridA = grid, gridB = grid, gridC = grid;
				bool first, third;
				///
				grid2 = grid;
				for (int row = 0; row < 9; row++)
				{
					for (int col = 0; col < 9; col++)
					{
						if (grid2[row][col].val == d)
						{
							for (int row2 = 0; row2 < 9; row2++)
							{
								for (int col2 = 0; col2 < 9; col2++)
								{
									if (row2 == row && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
									if (col2 == col && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
									if (grid2[row2][col2].box == grid2[row][col].box && grid2[row2][col2].val == 0)
										grid2[row2][col2].val = -1;
								}
							}
						}
					}
				}
				boxes = vector<short>(10, 0);
				rows = vector<short>(9, 0);
				cols = vector<short>(9, 0);
				for (int row = 0; row < 9; row++)
				{
					for (int col = 0; col < 9; col++)
					{
						if (grid2[row][col].val == 0)
						{
							rows[row]++;
							cols[col]++;
							boxes[grid2[row][col].box]++;
						}
					}
				}
				/// //trifectorize
				for (int b = 1; b < 10; b++)
					if (boxes[b] == 3)
					{
						first = true;
						third = false;
						for (int row = 0; row < 9; row++)
						{
							for (int col = 0; col < 9; col++)
							{
								if (grid2[row][col].val == 0 && grid2[row][col].box == b && first)
								{
									gridA[row][col].val = d;
									gridA2 = sudoku(gridA);
									if (full(gridA2))
										return gridA2;
									gridA[row][col].val = 0;
									first = false;
								}
								if (grid2[row][col].val == 0 && grid2[row][col].box == b && !first && !third)
								{
									gridB[row][col].val = d;
									gridB2 = sudoku(gridB);
									if (full(gridB2))
										return gridB2;
									gridB[row][col].val = 0;
									third = true;
								}
								if (grid2[row][col].val == 0 && grid2[row][col].box == b && third)
								{
									gridC[row][col].val = d;
									gridC2 = sudoku(gridC);
									if (full(gridC2))
										return gridC2;
									gridC[row][col].val = 0;
								}
							}
						}
					}
				for (int r = 0; r < 9; r++)
					if (rows[r] == 3)
					{
						first = true;
						third = false;
						for (int col = 0; col < 9; col++)
						{
							if (grid2[r][col].val == 0 && first)
							{
								gridA[r][col].val = d;
								gridA2 = sudoku(gridA);
								if (full(gridA2))
									return gridA2;
								gridA[r][col].val = 0;
								first = false;
							}
							if (grid2[r][col].val == 0 && !first && !third)
							{
								gridB[r][col].val = d;
								gridB2 = sudoku(gridB);
								if (full(gridB2))
									return gridB2;
								gridB[r][col].val = 0;
								third = true;
							}
							if (grid2[r][col].val == 0 && third)
							{
								gridC[r][col].val = d;
								gridC2 = sudoku(gridC);
								if (full(gridC2))
									return gridC2;
								gridC[r][col].val = 0;
							}
						}
					}
				for (int c = 0; c < 9; c++)
					if (cols[c] == 3)
					{
						first = true;
						third = false;
						for (int row = 0; row < 9; row++)
						{
							if (grid2[row][c].val == 0 && first)
							{
								gridA[row][c].val = d;
								gridA2 = sudoku(gridA);
								if (full(gridA2))
									return gridA2;
								gridA[row][c].val = 0;
								first = false;
							}
							if (grid2[row][c].val == 0 && !first && !third)
							{
								gridB[row][c].val = d;
								gridB2 = sudoku(gridB);
								if (full(gridB2))
									return gridB2;
								gridB[row][c].val = 0;
								third = true;
							}
							if (grid2[row][c].val == 0 && third)
							{
								gridC[row][c].val = d;
								gridC2 = sudoku(gridC);
								if (full(gridC2))
									return gridC2;
								gridC[row][c].val = 0;
							}
						}
					}
			}
			//*
			///
			done = true;
		}
	}
	return grid;
}
//*/

int nnysix()//solve the 50 sudoku puzzles in the file and sum the top left 3 digits as numbers as solution
{
	ifstream puzs("sudoku.txt");
	int total = 0;
	for (int i = 1; i <= 50; i++)//
	{
		vector<vector<Doku>> grid(9, vector<Doku>(9)), sol;
		for (int row = 0; row < 9; row++)
		{
			string temp;
			getline(puzs, temp);
			if(temp[0]=='G')
				getline(puzs, temp);
			for (int col = 0; col < 9; col++)
				grid[row][col].val = temp[col] - '0';
		}
		for (int row = 0; row < 9; row++)//set boxes
		{
			for (int col = 0; col < 9; col++)
			{
				if (row < 3 && col < 3)
					grid[row][col].box = 1;
				else if (row < 3 && col < 6)
					grid[row][col].box = 2;
				else if (row < 3)
					grid[row][col].box = 3;
				else if (row < 6 && col < 3)
					grid[row][col].box = 4;
				else if (row < 6 && col < 6)
					grid[row][col].box = 5;
				else if (row < 6)
					grid[row][col].box = 6;
				else if (col < 3)
					grid[row][col].box = 7;
				else if (col < 6)
					grid[row][col].box = 8;
				else
					grid[row][col].box = 9;
			}
		}
		cout << '\n' << i << "\n";
		sol = sudoku(grid);
		//*
		cout << "\n";
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				cout << sol[row][col].val << ' ';
			}
			cout << endl;
		}
		if (!correct(sol))
			cout << "FAIL.\n";
		//*/
		total += sol[0][0].val*100 + sol[0][1].val*10 + sol[0][2].val;
	}
	puzs.close();
	cout << total << endl;

	return 0;
}