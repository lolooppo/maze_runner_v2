#include <chrono>

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2


void init_grid(int, int);
void draw_grid();
void draw_grid_unit(int, int);
void draw_runner_unit();
void draw_target_unit();
void draw_wall_unit(int, int);
void move_runner();
bool valid_move(int, int);
bool win();
bool lose(std::chrono::time_point<std::chrono::system_clock>);
#endif // GAME_H_INCLUDED
