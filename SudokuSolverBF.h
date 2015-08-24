#ifndef sudokusolvebf_h
#define sudokusolvebf_h

#include "SudokuBoard.h"

class SudokuSolverBF
{
	SudokuBoard startboard;
	int defboard[9][9];
	int workboard[9][9];
	int pencilmarks[9][9][10];
	int pencilmarkscount[9][9];
	int pencilmarksrow[9][10];
	int pencilmarkscol[9][10];
	int pencilmarksbox[9][10];
	int pencilboxes;
public:
	int guesses;
	SudokuSolverBF(void);
	SudokuSolverBF(char *brd):startboard(brd) {}
	SudokuSolverBF(int *brd):startboard(brd) {}
	SudokuSolverBF(int **brd):startboard(brd) {}
	SudokuSolverBF(SudokuBoard brd):startboard(brd) {}
	SudokuBoard Solve(bool minimizetrials = false);
	bool solverand(bool minimizetrials = false);
	bool IsOK(int r, int c, int val);
	int processPencilMarks();
	int processNakedSets(int level);   // Up to quads (level <= 4)
	int processHiddenSets(int level);  // Up to quads (level <= 4)
	int processHiddenPairs();
	//int go(int r, int c);
	void makepencilmarks();
	~SudokuSolverBF(void);
};

#endif
