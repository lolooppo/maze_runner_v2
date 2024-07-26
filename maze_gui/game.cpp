#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include "game.h"

int grid_x, grid_y;
int pos_x = 1, pos_y = 38;
short s_direction = RIGHT;

void init_grid(int x, int y){
    grid_x = x, grid_y = y;
}

void draw_grid(){
    for(int x=0; x<grid_x; x++){
        for(int y=0; y<grid_y; y++){
            draw_grid_unit(x, y);
        }
    }
}

void draw_grid_unit(int x, int y){
    //change the width and the color of the borders.
    if(x==0 or y==0 or x==grid_x-1 or y==grid_y-1){
        glLineWidth(3.0);
        glColor3f(0.0, 0.0, 1.0);
    }else{
        glLineWidth(1.0);
        glColor3f(0.0, 0.0, 0.0);
    }

    //draw the pixel coordinates(4-lines).
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glVertex2f(x, y+1);
    glEnd();
}

void draw_snack(){
    if(s_direction == UP)
        pos_y++;
    if(s_direction == DOWN)
        pos_y--;
    if(s_direction == LEFT)
        pos_x--;
    if(s_direction == RIGHT)
        pos_x++;
    glRectd(pos_x, pos_y, pos_x+1, pos_y+1);
}
