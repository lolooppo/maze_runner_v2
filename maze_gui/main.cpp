#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"
#include "maze.h"

#define COLUMNS 41
#define ROWS 41

#define FPS 20

extern short next_direction;//store the next direction of the runner


void display_call_back();
void reshape_call_back(int W, int H);
void timer_call_back(int);
void keyboard_call_back(int, int, int);
void init_color();



std::chrono::time_point<std::chrono::system_clock> Start;//stores the current time before starting the game



int main(int argc, char **argv){
    generate_maze();
    Start = std::chrono::system_clock::now();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Welcome to the JUNGLE");
    glutDisplayFunc(display_call_back);
    glutReshapeFunc(reshape_call_back);
    glutTimerFunc(0, timer_call_back, 0);
    glutSpecialFunc(keyboard_call_back);
    init_color();
    glutMainLoop();
    return 0;
}


//initialize the color of the grid lines
void init_color(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    init_grid(COLUMNS, ROWS);
}



void display_call_back(){
    glClear(GL_COLOR_BUFFER_BIT);

    //check win
    if(win()){
        MessageBox(NULL, "\tYOU DID IT BEFORE THE TIME ENDS", "\t\tCONGRATS", 100);
        exit(0);
    }
    //check lose
    if(lose(Start)){
        MessageBox(NULL, "\tYOU LOST", "\t\tSORRY", 100);
        exit(0);
    }

    move_runner();
    draw_grid();
    next_direction = 0;//reset to 0, to prevent keep moving without key pressing
    glutSwapBuffers();
}



void reshape_call_back(int W, int H){
    glViewport(0, 0, (GLsizei)W, (GLsizei)H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}



void timer_call_back(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer_call_back, 0);
}


//handles the keyboard hit
void keyboard_call_back(int key, int, int){
    switch(key){
        case GLUT_KEY_UP:
            next_direction = UP;
            break;
        case GLUT_KEY_DOWN:
            next_direction = DOWN;
            break;
        case GLUT_KEY_LEFT:
            next_direction = LEFT;
            break;
        case GLUT_KEY_RIGHT:
            next_direction = RIGHT;
            break;
    }
}
