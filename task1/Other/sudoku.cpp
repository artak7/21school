// Author Artak

// #include <bits/stdc++.h>
// using namespace std;
// #include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 10 // const int N = 10;
bool used_col[N][N], used_row[N][N], used_sqr[N][N];
int sudoku[N][N], sqr_id[N][N];

bool ok(int i, int j, int x)
{
	// fprintf(stderr, "%d %d %d %d %d\n", used_row[i][x], used_col[j][x], used_sqr[sqr_id[i][j]][x], sqr_id[i][j], x); //
	return !(used_row[i][x] || used_col[j][x] || used_sqr[sqr_id[i][j]][x]);
}

struct tuple
{
	bool f;
	int i, j;
	tuple(){};
	tuple(bool f, int i, int j) {this->f = f; this->i = i; this->j = j;}
};

tuple find_next(int i, int j)
{
	int i1, j1;
	bool next_found = false;
	for (i1 = i; !next_found && i1 < N; i1++)
		for (j1 = j * (i1 == i) + 1; !next_found && j1 < N; j1++)
			next_found = sudoku[i1][j1] == 0;
	
	tuple result(next_found, --i1, --j1);
	// result.i = --i1;
	// result.j = --j1;
	// result.f = next_found;
	return result;
}

bool solve(int i, int j)
{
	fprintf(stderr, "currs:%d,%d\n", i, j); //

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

	tuple t = find_next(i, j);
	bool next_found = t.f;
	int next_i = t.i;
	int next_j = t.j;

	if (next_found)	//
		fprintf(stderr, "nexts:%d,%d\n", next_i, next_j); //

	if (sudoku[i][j] > 0) 
		if (next_found) 
		{
			fputs("\n", stderr); //
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

			for (int i1 = 1; i1 < N; i1++, fputs("\n", stderr)) //
				for (int j1 = 1; j1 < N; j1++) //
					fprintf(stderr, "%d", sudoku[i1][j1]); //

			fputs("\n", stderr); //

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
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	// FILE* in = fopen("input.txt", "r");
	// FILE* out = fopen("output.txt", "w+");
}

void read()
{
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			int num_of_sqr = (i - 1) / 3 * 3 + (j + 2) / 3; 
			sqr_id[i][j] = num_of_sqr;

			char c = getc(stdin);
			if (c == '\n') c = getc(stdin);

			if (c != '.')
			{
				int x = c - 48;
				sudoku[i][j] = x;
				used_row[i][x] = true;
				used_col[j][x] = true;
				used_sqr[sqr_id[i][j]][x] = true;
			}
		}
	}
}

void print(bool WellDone)
{
	if (WellDone)
	{
		for (int i = 1; i < N; i++, puts(""))
			for (int j = 1; j < N; j++)
				printf("%d", sudoku[i][j]);
	}
	else
	{ 
		puts("Error");
	}
}

int main()
{
	files();
	read();
	bool WellDone = solve(1, 1);
	print(WellDone);
	return 0;
}