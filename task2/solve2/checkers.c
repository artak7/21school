//Author Artak
#include <stdio.h>
#include <stdbool.h>
#define N 9 // const int N = 9;
#define N_CHECKERS 12 // const int N_CHECKERS = 12;
#define EMPTY_CELL '.' // const char EMPTY_CELL = '.'

const int move_x[4] = {1, 1, -1, -1}; 
const int move_y[4] = {-1, 1, -1, 1};

typedef struct 
{
	int x, y;
} pair;

/*
struct list
{
	pair data;
	list* top;//?
	list* next;
}

void top(list *l)  //?
{
	l->top=l->top->next;
}

pair front(list *l) //?
{
	return l->top->data;
}

void push(list *l, pair data) //?
{
	list m;
	m->data = data;
	m->next = l->next;
	l->next = m;
}
*/

/*
//bool beaten[N][N]; 
int depth[N][N];
pair parent[N][N];

bool bfs(pair start, int T)
{
	queue <pair> q; // rewrite to c
	q.push(start);

	// delete ?
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
		{
			//beaten[i][j] = false;
			depth[i][j] = 0;
			parent[i][j].x = 0;
			parent[i][j].y = 0;		
		}

	//beaten[start.x][start.y] = true;
	depth[start.x][start.y] = 0;
	parent[start.x][start.y].x = -1;
	parent[start.x][start.y].y = -1;
	while (!q.empty())
	{
		pair curr_cell = q.front(); q.pop();
		for (int i = 0; i < 2 * T; i++)
		{
			pair move2cell;
			move2cell.x = curr_cell.x + 2 * move_x[i];
			move2cell.y = curr_cell.y + 2 * move_y[i];
			if (0 < move2cell.x && move2cell.x < N &&
				0 < move2cell.y && move2cell.y < N &&
				!(T == 1 && curr_cell.x == 8)) // just turned into lady
			{
				int beaten_cell_x = move2cell.x - move_x[i];
				int beaten_cell_y = move2cell.y - move_y[i]; 
				char beaten_cell = map_board[beaten_cell_x][beaten_cell_y];
				char next_cell = map_board[move2cell.x][move2cell.y];
				if ((beaten_cell == 'b' || beaten_cell == 'B') && 
					(next_cell == EMPTY_CELL || move2cell.x == start_cell.x && move2cell.y == start_cell.y) && 
					!beaten[beaten_cell_x][beaten_cell_y];)
				{
					int d = depth[curr_cell.x][curr_cell.y];
					if (d + 1 > depth[move2cell.x][move2cell.y]) // max_depth?
					{
						q.push(move2cell);
						beaten[beaten_cell_x][beaten_cell_y] = true;
						depth[move2cell.x][move2cell.y] = d + 1;
						parent[move2cell.x][move2cell.y].x = curr_cell.x; // c constructor
						parent[move2cell.x][move2cell.y].y = curr_cell.y;
					}
				}
			}
		}
	}
}
*/

char map_board[N][N];
bool beaten[N][N];
pair path[N_CHECKERS], max_path[N_CHECKERS], start_cell;
int max_depth = -1;

void dfs(pair curr_cell, int T, int depth)
{
	path[depth].x = curr_cell.x;
	path[depth].y = curr_cell.y;

	if (depth > max_depth)
	{
		max_depth = depth; 
		for (int i = 0; i <= max_depth; i++)
		{
			max_path[i].x = path[i].x;
			max_path[i].y = path[i].y;

			fprintf(stderr, "%d,%d-", path[i].x, path[i].y); //
		}
		fputs("\n", stderr); //
	}
	
	for (int i = 0; i < 2 * T; i++)
	{
		pair move2cell;
		move2cell.x = curr_cell.x + 2 * move_x[i];
		move2cell.y = curr_cell.y + 2 * move_y[i];
		if (0 < move2cell.x && move2cell.x < N &&
			0 < move2cell.y && move2cell.y < N &&
			!(T == 1 && curr_cell.x == 8)) // newly turned into lady
		{
			int beaten_cell_x = move2cell.x - move_x[i];
			int beaten_cell_y = move2cell.y - move_y[i]; 
			char beaten_cell = map_board[beaten_cell_x][beaten_cell_y];
			char next_cell = map_board[move2cell.x][move2cell.y];
			if ((beaten_cell == 'b' || beaten_cell == 'B') && 
				(next_cell == EMPTY_CELL || move2cell.x == start_cell.x && move2cell.y == start_cell.y)
				&& !beaten[beaten_cell_x][beaten_cell_y])
			{
				fprintf(stderr, "%d,%d %c\n", curr_cell.x, curr_cell.y, map_board[curr_cell.x][curr_cell.y]); //
				fprintf(stderr, "%d,%d %c\n", beaten_cell_x, beaten_cell_y, map_board[beaten_cell_x][beaten_cell_y]); //
				fprintf(stderr, "%d,%d %c\n", move2cell.x, move2cell.y, map_board[move2cell.x][move2cell.y]); //
				fprintf(stderr, "%d,%d %c\n", start_cell.x, start_cell.y, next_cell); //
				fputs("-----\n", stderr); //

				beaten[beaten_cell_x][beaten_cell_y] = true;
				dfs(move2cell, T, depth + 1);
				beaten[beaten_cell_x][beaten_cell_y] = false;
			}
		}
	}
}

void init(pair cell)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			beaten[i][j] = false;

	path[0].x = start_cell.x = cell.x;
	path[0].y = start_cell.y = cell.y;
}

void solve()
{
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
		{
			pair cell; cell.x = i; cell.y = j;
			if (map_board[cell.x][cell.y] == 'w') { init(cell); dfs(cell, 1, 0); }
			if (map_board[cell.x][cell.y] == 'W') { init(cell); dfs(cell, 2, 0); }
		}
}

void files()
{
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stderr);
	//FILE* in = fopen("input.txt", "r");
	//FILE* out = fopen("output.txt", "w");
}

bool read(int argc, char* argv[])
{
	if (argc != N)
		return false;

	int w_ch = 0, b_ch = 0;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			//char c = getc(stdin);
			char c = argv[i][j-1];
			if (c == 'w'|| c == 'W')
			{
				if ((i + j) % 2 == 1)
					return false;

				if (i == N - 1 && c == 'w')
					return false;

				w_ch++;
			}
			else if (c == 'b' || c == 'B')
			{
				if ((i + j) % 2 == 1)
					return false;

				if (i == 1 && c == 'b')
					return false;

				b_ch++;
			}
			else if (c == '\r' || c == '\n')
				{ j--; continue; }
			else if (c != EMPTY_CELL)
				return false;

			map_board[i][j] = c;
		}
		// c = getc(stdin); // \r
		// c = getc(stdin); // \n
	}

	if (w_ch == 0 || w_ch > N_CHECKERS || b_ch > N_CHECKERS)
		return false;

	return true;
}

void print(bool WellDone)
{
	if (WellDone)
	{
		for (int i = 0; i <= max_depth; i++)
		{
			printf("%c%d", max_path[i].y+64, max_path[i].x);
			if (i < max_depth) printf("-");
		}
		puts("");
	}
	else
	{
		puts("Error");
	}
	//getc(stdin);
}

int main(int argc, char*  argv[])
{
	files();
	bool WellDone = read(argc, argv);
	if (WellDone)
		solve();
	print(WellDone);
	return 0;
}

