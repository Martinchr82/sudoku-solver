#include "SudokuSolverBF.h"
#include <stdio.h>
#include <string.h>

SudokuSolverBF::SudokuSolverBF(void)
{
}

SudokuSolverBF::~SudokuSolverBF(void)
{
}

bool SudokuSolverBF::IsOK(int r, int c, int val)
{
	for(int i=0;i<9;++i)
	{
		if (i!=c && workboard[r][i]==val) return 0;
		if (i!=r && workboard[i][c]==val) return 0;
	}
	int rr = r - r%3, cc = c - c%3;
	for(int i=0;i<3;++i) 
		for(int j=0;j<3;++j)
			if (rr+i!=r && cc+j!=c && workboard[rr+i][cc+j]==val) return 0;
	return 1;
}


void SudokuSolverBF::makepencilmarks()
{
	for(int r=0;r<9;++r)
		for(int c=0;c<9;++c)
		{
			if (defboard[r][c]==0)
			{
				for(int i=1;i<=9;++i)
					if (IsOK(r, c, i))
					{
						pencilmarks[r][c][i] = 1;
						pencilmarkscount[r][c]++;
						pencilmarksrow[r][i]++;
						pencilmarkscol[c][i]++;
						pencilmarksbox[(r/3)*3 + c/3][i]++;
					}
			}
		}
}

int SudokuSolverBF::processPencilMarks() {
	int ret = 0;
	int tind = 0;
	for(int r=0;r<9;++r)
		for(int c=0;c<9;++c)
		{
			if (pencilmarkscount[r][c]==1)
			{
				for(tind=1;pencilmarks[r][c][tind]==0;tind++);
				defboard[r][c] = workboard[r][c] = tind;
				pencilmarkscount[r][c] = 0;
				pencilmarks[r][c][tind] = 0;
				pencilmarksrow[r][tind]--;
				pencilmarkscol[c][tind]--;
				pencilmarksbox[(r/3)*3 + c/3][tind]--;
				for(int rr=0;rr<9;rr++)
				{
					if (pencilmarks[rr][c][tind])
					{
						pencilmarks[rr][c][tind] = 0;
						pencilmarkscount[rr][c]--;
						if (defboard[rr][c]==0 && pencilmarkscount[rr][c]==0) return -1;
						pencilmarksrow[rr][tind]--;
						pencilmarkscol[c][tind]--;
						pencilmarksbox[(rr/3)*3 + c/3][tind]--;
					}
				}
				for(int cc=0;cc<9;cc++)
				{
					if (pencilmarks[r][cc][tind])
					{
						pencilmarks[r][cc][tind] = 0;
						pencilmarkscount[r][cc]--;
						if (defboard[r][cc]==0 && pencilmarkscount[r][cc]==0) return -1;
						pencilmarksrow[r][tind]--;
						pencilmarkscol[cc][tind]--;
						pencilmarksbox[(r/3)*3 + cc/3][tind]--;
					}
				}
				int rr = r - r%3, cc = c - c%3;
				for(int i=0;i<3;++i) 
					for(int j=0;j<3;++j)
						if (pencilmarks[rr+i][cc+j][tind])
						{
							pencilmarks[rr+i][cc+j][tind] = 0;
							pencilmarkscount[rr+i][cc+j]--;
							if (defboard[rr+i][cc+j]==0 && pencilmarkscount[rr+i][cc+j]==0) return -1;
							pencilmarksrow[rr+i][tind]--;
							pencilmarkscol[cc+j][tind]--;
							pencilmarksbox[((rr+i)/3)*3 + (cc+j)/3][tind]--;
						}
				ret++;
				continue;
			}

			for(int m=1;m<=9;++m)
				if (pencilmarks[r][c][m] && 
					(pencilmarksrow[r][m]==1 || 
						pencilmarkscol[c][m]==1 || 
						pencilmarksbox[(r/3)*3 + c/3][m]==1))
				{
					defboard[r][c] = workboard[r][c] = m;
					pencilmarkscount[r][c] = 0;
					pencilmarks[r][c][m] = 0;
					pencilmarksrow[r][m]--;
					pencilmarkscol[c][m]--;
					pencilmarksbox[(r/3)*3 + c/3][m]--;
					for(int k=1;k<=9;++k)
					{
						if (pencilmarks[r][c][k])
						{
							pencilmarksrow[r][k]--;
							pencilmarkscol[c][k]--;
							pencilmarksbox[(r/3)*3 + c/3][k]--;
							pencilmarks[r][c][k] = 0;
						}
					}
					for(int rr=0;rr<9;rr++)
					{
						if (pencilmarks[rr][c][m])
						{
							pencilmarks[rr][c][m] = 0;
							pencilmarkscount[rr][c]--;
							if (defboard[rr][c]==0 && pencilmarkscount[rr][c]==0) return -1;
							pencilmarksrow[rr][m]--;
							pencilmarkscol[c][m]--;
							pencilmarksbox[(rr/3)*3 + c/3][m]--;
						}
					}
					for(int cc=0;cc<9;cc++)
					{
						if (pencilmarks[r][cc][m])
						{
							pencilmarks[r][cc][m] = 0;
							pencilmarkscount[r][cc]--;
							if (defboard[r][cc]==0 && pencilmarkscount[r][cc]==0) return -1;
							pencilmarksrow[r][m]--;
							pencilmarkscol[cc][m]--;
							pencilmarksbox[(r/3)*3 + cc/3][m]--;
						}
					}
					int rr = r - r%3, cc = c - c%3;
					for(int i=0;i<3;++i) 
						for(int j=0;j<3;++j)
							if (pencilmarks[rr+i][cc+j][m])
							{
								pencilmarks[rr+i][cc+j][m] = 0;
								pencilmarkscount[rr+i][cc+j]--;
								if (defboard[rr+i][cc+j]==0 && pencilmarkscount[rr+i][cc+j]==0) return -1;
								pencilmarksrow[rr+i][m]--;
								pencilmarkscol[cc+j][m]--;
								pencilmarksbox[((rr+i)/3)*3 + (cc+j)/3][m]--;
							}
					ret++;
					break;
				}
		}
	return ret;
}

int SudokuSolverBF::processNakedSets(int level) {
	if (level<2 || level>4) return 0;
	int marks[4][2];
	int cand[5];
	int valflags[10];
	for(int i=1;i<=9;++i) valflags[i] = 0;
	int lev;
	int ret = 0;

	// Rows
	for(int r=0;r<9;++r) {
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarksrow[r][cand[lev]]>=2) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				for(int c=0;c<9;++c) {
					int tsum = 0;
					flags[c] = 0;
					for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
					if (tsum>0 && tcount<level && tsum==pencilmarkscount[r][c]) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[c] = 1; }
					else if (tsum>0 && tsum==pencilmarkscount[r][c]) return -1; // Too many cells, too few options
				}
				if (tcount==level) { // Found naked multiple
					for(int c=0;c<9;++c) {
						if (flags[c]==0) 
							for(int i=0;i<level;++i)
								if (pencilmarks[r][c][cand[i]]==1) {
									ret++; 
									pencilmarks[r][c][cand[i]] = 0; 
									pencilmarkscount[r][c]--;
									if (pencilmarkscount[r][c]==0) return -1;
									pencilmarksrow[r][cand[i]]--;
									pencilmarkscol[c][cand[i]]--;
									pencilmarksbox[(r/3)*3 + c/3][cand[i]]--;
								}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	//return ret;
	// Columns
	for(int c=0;c<9;++c) {
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarkscol[c][cand[lev]]>=2) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				for(int r=0;r<9;++r) {
					int tsum = 0;
					flags[r] = 0;
					for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
					if (tsum>0 && tcount<level && tsum==pencilmarkscount[r][c]) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[r] = 1; }
					else if (tsum>0 && tsum==pencilmarkscount[r][c]) return -1; // Too many cells, too few options
				}
				if (tcount==level) { // Found naked multiple
					for(int r=0;r<9;++r) {
						if (flags[r]==0) 
							for(int i=0;i<level;++i)
								if (pencilmarks[r][c][cand[i]]==1) {
									ret++; 
									pencilmarks[r][c][cand[i]] = 0; 
									pencilmarkscount[r][c]--;
									if (pencilmarkscount[r][c]==0) return -1;
									pencilmarksrow[r][cand[i]]--;
									pencilmarkscol[c][cand[i]]--;
									pencilmarksbox[(r/3)*3 + c/3][cand[i]]--;
								}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	// Boxes
	for(int box=0;box<9;++box) {
		int rr = (box / 3) * 3;
		int cc = (box % 3) * 3;
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarksbox[box][cand[lev]]>=2) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				int ind = 0;
				for(int r=rr;r<rr+3;++r)
					for(int c=cc;c<cc+3;++c) {
						ind++;
						int tsum = 0;
						flags[ind] = 0;
						for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
						if (tsum>0 && tcount<level && tsum==pencilmarkscount[r][c]) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[ind] = 1; }
						else if (tsum>0 && tsum==pencilmarkscount[r][c]) return -1; // Too many cells, too few options
				}
				if (tcount==level) { // Found naked multiple
					ind = 0;
					for(int r=rr;r<rr+3;++r)
						for(int c=cc;c<cc+3;++c) {
							ind++;
							if (flags[ind]==0) 
								for(int i=0;i<level;++i)
									if (pencilmarks[r][c][cand[i]]==1) {
										ret++; 
										pencilmarks[r][c][cand[i]] = 0; 
										pencilmarkscount[r][c]--;
										if (pencilmarkscount[r][c]==0) return -1;
										pencilmarksrow[r][cand[i]]--;
										pencilmarkscol[c][cand[i]]--;
										pencilmarksbox[box][cand[i]]--;
									}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	return ret;
}

int SudokuSolverBF::processHiddenSets(int level) {
	if (level<2 || level>4) return 0;
	int marks[4][2];
	int cand[5];
	int valflags[10];
	for(int i=1;i<=9;++i) valflags[i] = 0;
	int lev;
	int ret = 0;

	// Rows
	for(int r=0;r<9;++r) {
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarksrow[r][cand[lev]]>=2 && pencilmarksrow[r][cand[lev]]<=level) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				for(int c=0;c<9;++c) {
					int tsum = 0;
					flags[c] = 0;
					for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
					if (tsum>0 && tcount<level) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[c] = 1; }
					else if (tsum>0) tcount++;
					//if (tsum>0 && tcount<level && tsum==pencilmarkscount[r][c]) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[c] = 1; }
					//else if (tsum>0 && tsum==pencilmarkscount[r][c]) return -1; // Too many cells, too few options
				}
				if (tcount==level) { // Found hidden multiple
					for(int c=0;c<9;++c) {
						if (flags[c]==1) 
							for(int i=1;i<=9;++i)
								if (valflags[i]==0)
									if (pencilmarks[r][c][i]==1) {
										ret++; 
										pencilmarks[r][c][i] = 0; 
										pencilmarkscount[r][c]--;
										if (pencilmarkscount[r][c]==0) return -1;
										pencilmarksrow[r][i]--;
										pencilmarkscol[c][i]--;
										pencilmarksbox[(r/3)*3 + c/3][i]--;
									}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	//return ret;
	// Columns
	for(int c=0;c<9;++c) {
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarkscol[c][cand[lev]]>=2 && pencilmarkscol[c][cand[lev]]<=level) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				for(int r=0;r<9;++r) {
					int tsum = 0;
					flags[r] = 0;
					for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
					if (tsum>0 && tcount<level) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[r] = 1; }
					else if (tsum>0) tcount++;
				}
				if (tcount==level) { // Found naked multiple
					for(int r=0;r<9;++r) {
						if (flags[r]==1) 
							for(int i=1;i<=9;++i)
								if (valflags[i]==0)
									if (pencilmarks[r][c][i]==1) {
										ret++; 
										pencilmarks[r][c][i] = 0; 
										pencilmarkscount[r][c]--;
										if (pencilmarkscount[r][c]==0) return -1;
										pencilmarksrow[r][i]--;
										pencilmarkscol[c][i]--;
										pencilmarksbox[(r/3)*3 + c/3][i]--;
									}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	// Boxes
	for(int box=0;box<9;++box) {
		int rr = (box / 3) * 3;
		int cc = (box % 3) * 3;
		lev = 0;
		cand[0] = 0;
		while (lev>=0) {
			if (lev<level) {
				cand[lev]++;
				if (cand[lev]>9) { 
					lev--; 
					if (lev>=0) valflags[cand[lev]] = 0; 
					continue; 
				}
				if (valflags[cand[lev]]==0 && pencilmarksbox[box][cand[lev]]>=2 && pencilmarksbox[box][cand[lev]]<=level) { 
					valflags[cand[lev]] = 1; 
					lev++; 
					cand[lev] = 0;  
					continue; 
				}
				else continue;
			}
			else {
				int tcount = 0;
				int flags[9];
				int ind = 0;
				for(int r=rr;r<rr+3;++r)
					for(int c=cc;c<cc+3;++c) {
						ind++;
						int tsum = 0;
						flags[ind] = 0;
						for(int i=0;i<level;++i) tsum += pencilmarks[r][c][cand[i]];
						if (tsum>0 && tcount<level) { marks[tcount][0] = r; marks[tcount][1] = c; tcount++; flags[ind] = 1; }
						else if (tsum>0) tcount++;
				}
				if (tcount==level) { // Found naked multiple
					ind = 0;
					for(int r=rr;r<rr+3;++r)
						for(int c=cc;c<cc+3;++c) {
							ind++;
							if (flags[ind]==1) 
								for(int i=1;i<=9;++i)
									if (valflags[i]==0)
										if (pencilmarks[r][c][i]==1) {
											ret++; 
											pencilmarks[r][c][i] = 0; 
											pencilmarkscount[r][c]--;
											if (pencilmarkscount[r][c]==0) return -1;
											pencilmarksrow[r][i]--;
											pencilmarkscol[c][i]--;
											pencilmarksbox[box][i]--;
										}
					}
				}
				lev--;
				if (lev>=0) valflags[cand[lev]] = 0; 
			}
		}
	}

	return ret;
}

int SudokuSolverBF::processHiddenPairs() {
	int ret = 0;
	// Rows
	for(int r=0;r<9;++r) {
		for(int p1=1;p1<=9;p1++)
			if (pencilmarksrow[r][p1]==2) 
				for(int p2=1;p2<=9;p2++) 
					if (p2!=p1 && pencilmarksrow[r][p2]==2) {
						int tcnt = 0, ind1 = 0, ind2 = 0;
						for(int c=0;c<9;++c) {
							if (pencilmarks[r][c][p1]==1 && pencilmarks[r][c][p2]==1) {
								tcnt++;
								if (tcnt==1) ind1 = c;
								else if (tcnt==2) ind2 = c;
							}
						}
						if (tcnt==2) {
							for(int i=1;i<=9;++i) {
								if (i!=p1 && i!=p2 && pencilmarks[r][ind1][i]==1) { 
									ret++; 
									pencilmarks[r][ind1][i] = 0; 
									pencilmarkscount[r][ind1]--;
									if (pencilmarkscount[r][ind1]==0) return -1;
									pencilmarksrow[r][i]--;
									pencilmarkscol[ind1][i]--;
									pencilmarksbox[(r/3)*3 + ind1/3][i]--;
								}
								if (i!=p1 && i!=p2 && pencilmarks[r][ind2][i]==1) { 
									ret++; 
									pencilmarks[r][ind2][i] = 0; 
									pencilmarkscount[r][ind2]--;
									if (pencilmarkscount[r][ind2]==0) return -1;
									pencilmarksrow[r][i]--;
									pencilmarkscol[ind2][i]--;
									pencilmarksbox[(r/3)*3 + ind2/3][i]--;
								}
							}
						}
					}
	}

	// Columns
	for(int c=0;c<9;++c) {
		for(int p1=1;p1<=9;p1++)
			if (pencilmarkscol[c][p1]==2) 
				for(int p2=1;p2<=9;p2++) 
					if (p2!=p1 && pencilmarkscol[c][p2]==2) {
						int tcnt = 0, ind1 = 0, ind2 = 0;
						for(int r=0;r<9;++r) {
							if (pencilmarks[r][c][p1]==1 && pencilmarks[r][c][p2]==1) {
								tcnt++;
								if (tcnt==1) ind1 = r;
								else ind2 = r;
							}
						}
						if (tcnt==2) {
							for(int i=1;i<=9;++i) {
								if (i!=p1 && i!=p2 && pencilmarks[ind1][c][i]==1) { 
									ret++; 
									pencilmarks[ind1][c][i] = 0; 
									pencilmarkscount[ind1][c]--;
									pencilmarksrow[ind1][i]--;
									pencilmarkscol[c][i]--;
									pencilmarksbox[(ind1/3)*3 + c/3][i]--; 
								}
								if (i!=p1 && i!=p2 && pencilmarks[ind2][c][i]==1) { 
									ret++; 
									pencilmarks[ind2][c][i] = 0; 
									pencilmarkscount[ind2][c]--;
									pencilmarksrow[ind2][i]--;
									pencilmarkscol[c][i]--;
									pencilmarksbox[(ind2/3)*3 + c/3][i]--; 
								}
							}
						}
					}
	}

	// Boxes
	for(int box=0;box<9;++box) {
		int rr = (box / 3) * 3;
		int cc = (box % 3) * 3;
		for(int p1=1;p1<=9;p1++)
			if (pencilmarksbox[box][p1]==2) 
				for(int p2=1;p2<=9;p2++) 
					if (p2!=p1 && pencilmarksbox[box][p2]==2) {
						int tcnt = 0, ind1r = 0, ind1c = 0, ind2r = 0, ind2c = 0;
						for(int r=rr;r<rr+3;++r)
							for(int c=cc;c<cc+3;++c) {
								if (pencilmarks[r][c][p1]==1 && pencilmarks[r][c][p2]==1) {
									tcnt++;
									if (tcnt==1) { ind1r = r; ind1c = c; }
									else { ind2r = r; ind2c = c; }
								}
							}
						if (tcnt==2) {
							for(int i=1;i<=9;++i) {
								if (i!=p1 && i!=p2 && pencilmarks[ind1r][ind1c][i]==1) { 
									ret++; 
									pencilmarks[ind1r][ind1c][i] = 0; 
									pencilmarkscount[ind1r][ind1c]--;
									pencilmarksrow[ind1r][i]--;
									pencilmarkscol[ind1c][i]--;
									pencilmarksbox[box][i]--; 
								}
								if (i!=p1 && i!=p2 && pencilmarks[ind2r][ind2c][i]==1) { 
									ret++; 
									pencilmarks[ind2r][ind2c][i] = 0; 
									pencilmarkscount[ind2r][ind2c]--;
									pencilmarksrow[ind2r][i]--;
									pencilmarkscol[ind2c][i]--;
									pencilmarksbox[box][i]--; 
								}
							}
						}
					}
	}
	return ret;
}

bool SudokuSolverBF::solverand(bool minimizetrials)
{
	bool fla = 1;
	int tind = 0;
	// Repeat until no way to proceed except trial and error way
	while(1)
	{
		// Check if already solved
		int pc = 0;
		for(int r=0;r<9;++r)
			for(int c=0;c<9;++c)
				if (pencilmarkscount[r][c]>0) { pc = 1; break; }
		if (pc==0) return 1;

		int tret = processPencilMarks();
		if (tret==-1) return 0;
		else if (tret>0) continue;

		// Hidden pairs
		/*if (1) {
			tret = processHiddenPairs();
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}*/
		if (1) {
			tret = processHiddenSets(2);
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		// Hidden triples
		if (minimizetrials) {
			tret = processHiddenSets(3);
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		// Hidden quads
		if (minimizetrials) {
			tret = processHiddenSets(4);
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		// Naked pairs
		if (minimizetrials) {
			tret = processNakedSets(2);	
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		// Naked triples
		if (minimizetrials) {
			tret = processNakedSets(3);	
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		// Naked quads
		if (minimizetrials) {
			tret = processNakedSets(4);	
			if (tret==-1) return 0;
			else if (tret>0) continue;
		}

		if (tret==0) break;
		//break;
	}

	// Trial and error

	int tr;
	int defboard_backup[9][9];
	int workboard_backup[9][9];
	int pencilmarks_backup[9][9][10];
	int pencilmarkscount_backup[9][9];
	int pencilmarksrow_backup[9][10];
	int pencilmarkscol_backup[9][10];
	int pencilmarksbox_backup[9][10];
	memcpy(defboard_backup, defboard, sizeof(defboard_backup));
	memcpy(workboard_backup, workboard, sizeof(workboard_backup));
	memcpy(pencilmarks_backup, pencilmarks, sizeof(pencilmarks_backup));
	memcpy(pencilmarkscount_backup, pencilmarkscount, sizeof(pencilmarkscount_backup));
	memcpy(pencilmarksrow_backup, pencilmarksrow, sizeof(pencilmarksrow_backup));
	memcpy(pencilmarkscol_backup, pencilmarkscol, sizeof(pencilmarkscol_backup));
	memcpy(pencilmarksbox_backup, pencilmarksbox, sizeof(pencilmarksbox_backup));

	// Find the cell with minimum number of options
	int cmin = 11, cind = -1;
	int crow, ccol;
	for(int r=0;r<9;++r)
		for(int c=0;c<9;++c)
			if (pencilmarkscount[r][c]<cmin && pencilmarkscount[r][c]>0)
			{
				cmin = pencilmarkscount[r][c];
				cind = 9*r + c;
			}

	// Check if already solved
	if (cmin==11) return 1;


	crow = cind/9;
	ccol = cind%9;
	bool fl1 = 1;
	for(int m=1;m<=9;++m)
		if (pencilmarks[crow][ccol][m])
		{
			fl1 = 1;
			defboard[crow][ccol] = workboard[crow][ccol] = m;
			pencilmarks[crow][ccol][m] = 0;
			pencilmarkscount[crow][ccol] = 0;

			pencilmarksrow[crow][m]--;
			pencilmarkscol[ccol][m]--;
			pencilmarksbox[(crow/3)*3 + ccol/3][m]--;
			for(int k=1;k<=9;++k)
			{
				if (pencilmarks[crow][ccol][k])
				{
					pencilmarksrow[crow][k]--;
					pencilmarkscol[ccol][k]--;
					pencilmarksbox[(crow/3)*3 + ccol/3][k]--;
					pencilmarks[crow][ccol][k] = 0;
				}
			}

			for(int rr=0;rr<9;rr++)
			{
				if (pencilmarks[rr][ccol][m])
				{
					pencilmarks[rr][ccol][m] = 0;
					pencilmarkscount[rr][ccol]--;
					if (defboard[rr][ccol]==0 && pencilmarkscount[rr][ccol]==0) fl1 = 0;
					pencilmarksrow[rr][m]--;
					pencilmarkscol[ccol][m]--;
					pencilmarksbox[(rr/3)*3 + ccol/3][m]--;
				}
			}
			for(int cc=0;cc<9;cc++)
			{
				if (pencilmarks[crow][cc][m])
				{
					pencilmarks[crow][cc][m] = 0;
					pencilmarkscount[crow][cc]--;
					if (defboard[crow][cc]==0 && pencilmarkscount[crow][cc]==0) fl1 = 0;
					pencilmarksrow[crow][m]--;
					pencilmarkscol[cc][m]--;
					pencilmarksbox[(crow/3)*3 + cc/3][m]--;
				}
			}
			int rr = crow - crow%3, cc = ccol - ccol%3;
			for(int i=0;i<3;++i) 
				for(int j=0;j<3;++j)
					if (pencilmarks[rr+i][cc+j][m])
					{
						pencilmarks[rr+i][cc+j][m] = 0;
						pencilmarkscount[rr+i][cc+j]--;
						if (defboard[rr+i][cc+j]==0 && pencilmarkscount[rr+i][cc+j]==0) fl1 = 0;
						pencilmarksrow[rr+i][m]--;
						pencilmarkscol[cc+j][m]--;
						pencilmarksbox[((rr+i)/3)*3 + (cc+j)/3][m]--;
					}

			if (fl1) { guesses++; tr = solverand(minimizetrials); }

			if (fl1 && tr) return 1;

			memcpy(defboard, defboard_backup, sizeof(defboard));
			memcpy(workboard, workboard_backup, sizeof(workboard));
			memcpy(pencilmarks, pencilmarks_backup, sizeof(pencilmarks));
			memcpy(pencilmarkscount, pencilmarkscount_backup, sizeof(pencilmarkscount));
			memcpy(pencilmarksrow, pencilmarksrow_backup, sizeof(pencilmarksrow));
			memcpy(pencilmarkscol, pencilmarkscol_backup, sizeof(pencilmarkscol));
			memcpy(pencilmarksbox, pencilmarksbox_backup, sizeof(pencilmarksbox));
		}
		return 0;
}

SudokuBoard SudokuSolverBF::Solve(bool minimizetrials)
{
	guesses = 0;
	SudokuBoard retbad;
	retbad.board[0][0] = -1;

	memcpy(workboard, startboard.board, 9*9*sizeof(int));
	memcpy(defboard, startboard.board, 9*9*sizeof(int));
	memset(pencilmarks, 0, sizeof(pencilmarks));
	memset(pencilmarkscount, 0, sizeof(pencilmarkscount));
	memset(pencilmarksrow, 0, sizeof(pencilmarksrow));
	memset(pencilmarkscol, 0, sizeof(pencilmarkscol));
	memset(pencilmarksbox, 0, sizeof(pencilmarksbox));
	makepencilmarks();

	for(int r=0;r<9;++r)
		for(int c=0;c<9;++c)
			if (defboard[r][c]==0 && pencilmarkscount[r][c]==0) return retbad;

	if (solverand(minimizetrials)) 
		return SudokuBoard((int**)workboard);
	else return retbad;
}
