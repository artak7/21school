// Author Artak
#include <stdio.h>
#include <stdbool.h>
#define N 10 // const int N = 10;
bool used_col[N][N], used_row[N][N], used_sqr[N][N];
int sudoku[N][N], sqr_id[N][N];

typedef struct
{
	bool f;
	int i, j;
} tuple;

void constructor(tuple* t, bool f, int i, int j)
{
	t->f = f;
	t->i = i;
	t->j = j;	
}

tuple find_next(int i, int j)
{
	int i1, j1;
	bool next_found = false;
	for (i1 = i; !next_found && i1 < N; i1++)
		for (j1 = j * (i1 == i) + 1; !next_found && j1 < N; j1++)
			next_found = sudoku[i1][j1] == 0;
	
	tuple result;
	constructor(&result, next_found, --i1, --j1);
	return result;
}

bool ok(int i, int j, int x)
{
	// fprintf(stderr, "%d %d %d %d %d\r\n", used_row[i][x], used_col[j][x], used_sqr[sqr_id[i][j]][x], sqr_id[i][j], x); //
	return !(used_row[i][x] || used_col[j][x] || used_sqr[sqr_id[i][j]][x]);
}

bool solve(int i, int j)
{
	fprintf(stderr, "currs:%d,%d\r\n", i, j); //

	// bool next_found = false;
	// int next_i, next_j;

	// for (int i1 = i; !next_found && i1 < N; i1++)
	// 	for (int j1 = j * (i1 == i) + 1; !next_found && j1 < N; j1++)
	// 		if (!sudoku[i1][j1])
	// 		{
	// 			next_found = true;
	// 			next_i = i1;
	// 			next_j = j1;
	// 		}

	tuple unzip = find_next(i, j);
	bool next_found = unzip.f;
	int next_i = unzip.i;
	int next_j = unzip.j;

	if (next_found)	//
		fprintf(stderr, "nexts:%d,%d\r\n", next_i, next_j); //

	if (sudoku[i][j] > 0) 
		if (next_found) 
		{
			fputs("\r\n", stderr); //
			bool done = solve(next_i, next_j);
			if (done) return true;
		}
		else
			return true;

	for (int x = 1; x < N; x++)
		if (ok(i, j, x))
		{
			used_row[i][x] = true;
			used_col[j][x] = true;
			used_sqr[sqr_id[i][j]][x] = true;
			sudoku[i][j] = x;

			for (int i1 = 1; i1 < N; i1++, fputs("\r\n", stderr)) //
				for (int j1 = 1; j1 < N; j1++) //
					fprintf(stderr, "%d", sudoku[i1][j1]); //

			fputs("\r\n", stderr); //

			if (!next_found) return true;
			bool done = solve(next_i, next_j);
			if (done) return true;

			used_row[i][x] = false;
			used_col[j][x] = false;
			used_sqr[sqr_id[i][j]][x] = false;
			sudoku[i][j] = 0;
		}

	return false;
}

void files()
{
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w+", stderr);
	// FILE* in = fopen("input.txt", "r");
	// FILE* out = fopen("output.txt", "w+");
}

bool read(int argc, char *argv[])
{
	if (argc != N)
		return false;

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			int num_of_sqr = (i - 1) / 3 * 3 + (j + 2) / 3; 
			sqr_id[i][j] = num_of_sqr;

			char c = argv[i][j-1];
			//char c = getc(stdin);

			//if (c == '\r') c = getc(stdin);
			//if (c == '\n') c = getc(stdin);
			
			if ('0' <= c && c <= '9')
			{
				int x = c - 48;
				if (!ok(i, j, x))
					return false;

				sudoku[i][j] = x;
				used_row[i][x] = true;
				used_col[j][x] = true;
				used_sqr[sqr_id[i][j]][x] = true;
			} else if (c == '\n' || c == '\r')
				{ j--; continue; }
			else if (c != '.')
				return false;
		}
		//if (c == '\n') c = gets(stdin);
		//if (c == '\r') c = getc(stdin);
	}

	return true;
}

void print(bool WellDone)
{
	if (WellDone)
	{
		for (int i = 1; i < N; i++, puts(""))
			for (int j = 1; j < N; j++)
				printf("%d ", sudoku[i][j]);
	}
	else
	{ 
		puts("Error");
	}
}

int main(int argc, char *argv[])
{
	bool WellDone;
	files();
	WellDone = read(argc, argv);
	if (WellDone)
		WellDone = solve(1, 1);
	print(WellDone);
	return 0;
}
