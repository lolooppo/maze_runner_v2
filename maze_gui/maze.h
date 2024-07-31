#include <bits/stdc++.h>

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

bool valid(int, int);
std::pair<int, int>get_row_column(int&);
void initialize_maze();
void generate_maze();
void print_maze();
bool dfs(int, int);
void solve_maze();
#endif // MAZE_H_INCLUDED
