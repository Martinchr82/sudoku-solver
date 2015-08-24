#include "SudokuBoard.h"
#include <string.h>
#include <cstdio>

SudokuBoard::SudokuBoard(void)
{
	memset(board, 0, 9*9*sizeof(int));
}

SudokuBoard::SudokuBoard(int **brd)
{
	memcpy(board, brd, 9*9*sizeof(int));
}

SudokuBoard::~SudokuBoard(void)
{
}

void SudokuBoard::Print()
{
	for(int i=0;i<9;++i)
	{
		int t = 0;
		for(int k=0;k<3;++k)
		{
			printf("%d %d %d ", board[i][t], board[i][t+1], board[i][t+2]);
			if (t!=6) printf("| ");
			t += 3;
		}
		printf("\n");
		if (i==2 || i==5) { for(int j=0;j<21;++j) printf("-"); printf("\n"); /*cout << "-"; cout << "\n";*/ }
	}
	printf("\n");
}
