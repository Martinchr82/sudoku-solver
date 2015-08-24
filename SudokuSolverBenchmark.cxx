#include "SudokuSolverBF.h"
#include <ctime>
#include <cstdio>
#include <algorithm>

using namespace std;

char sud[] = "..1.8.6.4.376.....5.............5.....6.1.8.....4.............3.....752.8.2.9.7..";
//char sud[] = "090700600000000051100032000804900000000000000000005307000190005560000000008007090";
//char sud[] = "7......1946.19.......6827.4.9......7...3..4.5..67.......1......2...74......2..3..";
//char sud[] = ".5..1.6.....5.6....6.4.7..2..8..9.45.1.3...8.79.2..3..2..6.5.9..8...3.....7.2..3.";
//char sud[] = "9..1.4..2.8..6..7..........4.......1.7.....3.3.......7..........3..7..8.1..2.9..4";
char sudo[500];
SudokuSolverBF *ssolv;

int main(int argc, char* argv[])
{
	bool verbose = true;
	verbose = false;
	if (argc<=1)
	{
		(SudokuBoard(sud)).Print();
		ssolv = new SudokuSolverBF((char*)sud);
		(ssolv->Solve()).Print();
		printf("Trials: %d\n", ssolv->guesses);
		printf("Running time: %lf s\n", clock()/(double)(CLOCKS_PER_SEC));
		//cout << "Running time: " << clock()/(double)(CLOCKS_PER_SEC) << " s\n";
		if (ssolv) delete ssolv;
		//system("PAUSE");
	}
	else
	{
		if (argc>2 && argv[2][0]=='-' && argv[2][1]=='v' && argv[2][2]==0) verbose = true;
		ssolv = new SudokuSolverBF();
		FILE *f;
		f = fopen(argv[1], "r");
		int count = 0;
		clock_t tbeg = clock();
		clock_t ttask = clock();
		SudokuBoard tmp;
		int totaltrials = 0;
		int solved = 0;
		while (fgets(sudo, 400, f)!=NULL)
		{
			count++;
			/*rep(i,81)
			{
				if (sudo[i]=='0') sudo[i] = '.';
				st[i/9][i%9] = wr[i/9][i%9] = sudo[i];
			}*/
			(*ssolv) = SudokuSolverBF((char*)sudo);
			tmp = ssolv->Solve();
			if (verbose) {
				printf("Puzzle #%d\tTrials: %d\tTime: %.3lf us\n", count, ssolv->guesses, (clock()-ttask)/(double)(CLOCKS_PER_SEC)*1.e6);
				ttask = clock();
			}
			totaltrials += ssolv->guesses;
			if (tmp.board[0][0]!=-1) solved++;
			//printf("%d Solved! Number of guesses: %d\n", count, ssolv->guesses);
			//printf("%d\t", count);
		}
		if (count==1) tmp.Print();
		if (ssolv) delete ssolv;
		printf("Total puzzles number %d\n", count);
		printf("Solved %d\n", solved);
		printf("Total trials %d\n", totaltrials);
		printf("Running time: %lf s\n", (clock()-tbeg)/(double)(CLOCKS_PER_SEC));
		if (count>0) printf("Average solution time: %.3lf microseconds\n", (clock()-tbeg)/(double)(CLOCKS_PER_SEC)/count*1.e6);
		fclose(f);
	}
	return 0;
}
