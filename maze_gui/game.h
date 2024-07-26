#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2


void init_grid(int x, int y);
void draw_grid();
void draw_grid_unit(int, int);
void draw_snack();
#endif // GAME_H_INCLUDED
