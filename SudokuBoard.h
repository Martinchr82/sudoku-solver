#ifndef sudokuboard_h
#define sudokuboard_h

class SudokuBoard
{
public:
	int board[9][9];
	SudokuBoard(void);
	SudokuBoard(char *brd)
	{
		for(int i=0;i<81;++i)
		{
			if (brd[i]=='.') board[i/9][i%9] = 0;
			else board[i/9][i%9] = (int)(brd[i]-'0');
		}
	}
	SudokuBoard(int *brd)
	{
		for(int i=0;i<81;++i)
		{
			board[i/9][i%9] = brd[i];
		}
	}
	SudokuBoard(int **brd);
	~SudokuBoard(void);
	void Print();
};

#endif