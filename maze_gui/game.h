#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2


void init_grid(int, int);
void draw_grid();
void draw_grid_unit(int, int);
void draw_snake_unit();
void draw_target_unit();
void draw_wall_unit(int, int);
void move_snake();
bool valid_move(int, int);
bool win();
#endif // GAME_H_INCLUDED
