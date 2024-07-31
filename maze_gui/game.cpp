#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include<ctime>
#include <chrono>
#include <mmsystem.h>
#include "game.h"

using namespace std;



extern char arr[41][41];
int grid_x, grid_y;
int runner_x = 0, runner_y = 39;
int target_x = 39, target_y = 1;
short next_direction = RIGHT;


//initialize the start drawing position
void init_grid(int x, int y){
    grid_x = x, grid_y = y;
}


//draw the grid
void draw_grid(bool is_lost = false){

    //set the position of the runner to the initial, to draw the solution from it to the target position
    if(is_lost){
        runner_x = 1, runner_y = 39;
    }

    for(int x=0; x<grid_x; x++){
        for(int y=0; y<grid_y; y++){
                if(x == runner_x and y == runner_y){
                    draw_runner_unit();
                }else if(x == target_x and y == target_y){
                    draw_target_unit();
                }else if(arr[x][y] == '-' or arr[x][y] == '!'){
                    draw_wall_unit(x, y);
                }else if(is_lost and arr[x][y] == 'S'){
                    draw_path_unit(x, y);
                }
                glColor3f(0.0, 0.0, 1.0);
                draw_grid_unit(x, y);
        }
    }
}



void draw_grid_unit(int x, int y){
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 1.0);

    //draw the 4 coordinates of each grid cell
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glVertex2f(x, y+1);
    glEnd();
}



void move_runner(){
    if(next_direction == UP and valid_move(runner_x, runner_y+1))
        runner_y++;
    if(next_direction == DOWN and valid_move(runner_x, runner_y-1))
        runner_y--;
    if(next_direction == LEFT and valid_move(runner_x-1, runner_y))
        runner_x--;
    if(next_direction == RIGHT and valid_move(runner_x+1, runner_y))
        runner_x++;
}



void draw_runner_unit(){
    glRectd(runner_x, runner_y, runner_x+1, runner_y+1);
}



void draw_target_unit(){
    glColor3f(0.0, 1.0, 0.0);
    glRectd(target_x, target_y, target_x+1, target_y+1);
}



void draw_wall_unit(int x,int y){
    glColor3f(1.0, 0.0, 0.0);
    glRectd(x, y, x+1, y+1);
}


void draw_path_unit(int x, int y){
    glColor3f(1.0f, 1.0f, 0.0f);
    glRectd(x, y, x+1, y+1);
}


bool win(){
    return runner_x == target_x and runner_y == target_y;
}
bool lose(chrono::time_point<std::chrono::system_clock> Start){
    auto End = std::chrono::system_clock::now();
    auto duration = End - Start;
    auto duration_seconds = std::chrono::duration_cast<chrono::seconds>(duration).count();
    return duration_seconds > 120;
}



bool valid_move(int x, int y){
    return x>=0 and x<=40 and y>=0 and y<=40 and (arr[x][y] == ' ' or arr[x][y] == 'S');
}
