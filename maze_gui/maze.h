#include <bits/stdc++.h>
using namespace std;

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

bool valid(int, int);
pair<int, int>get_row_column(int&);
void initialize_maze();
void generate_maze();
void print_maze();

#endif // MAZE_H_INCLUDED
