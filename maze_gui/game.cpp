#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include "game.h"

extern char arr[41][41];

int grid_x, grid_y;
int pos_x = 0, pos_y = 39;
int trgt_x = 39, trgt_y = 1;
short s_direction = RIGHT;

void init_grid(int x, int y){
    grid_x = x, grid_y = y;
}

void draw_grid(){
    for(int x=0; x<grid_x; x++){
        for(int y=0; y<grid_y; y++){
                if(x == pos_x and y == pos_y){
                    draw_snake_unit();
                }else if(x == trgt_x and y == trgt_y){
                    draw_target_unit();
                }else if(arr[x][y] != ' '){
                    draw_wall_unit(x, y);
                }
                draw_grid_unit(x, y);
        }
    }
}

void draw_grid_unit(int x, int y){
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 1.0);
    //draw the pixel coordinates(4-lines).
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glVertex2f(x, y+1);
    glEnd();
}

void move_snake(){
    if(s_direction == UP and valid_move(pos_x, pos_y+1))
        pos_y++;
    if(s_direction == DOWN and valid_move(pos_x, pos_y-1))
        pos_y--;
    if(s_direction == LEFT and valid_move(pos_x-1, pos_y))
        pos_x--;
    if(s_direction == RIGHT and valid_move(pos_x+1, pos_y))
        pos_x++;
}

void draw_snake_unit(){
    glRectd(pos_x, pos_y, pos_x+1, pos_y+1);
}

void draw_target_unit(){
    glColor3f(0.0, 1.0, 0.0);
    glRectd(trgt_x, trgt_y, trgt_x+1, trgt_y+1);
    glColor3f(0.0, 0.0, 1.0);
}

void draw_wall_unit(int x,int y){
    glColor3f(1.0, 0.0, 0.0);
    glRectd(x, y, x+1, y+1);
    glColor3f(0.0, 0.0, 1.0);
}

bool win(){
    return pos_x == trgt_x;
}

bool valid_move(int x, int y){
    return x>=0 and x<=40 and y>=0 and y<=40 and arr[x][y] == ' ' ;
}
