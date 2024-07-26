#include <GL/glu.h>
#include <GL/glut.h>
#include "game.h"

#define COLUMNS 40
#define ROWS 40

#define FPS 10

extern short s_direction;

void display_call_back();
void reshape_call_back(int W, int H);
void timer_call_back(int);
void keyboard_call_back(int, int, int);
void init_color();

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Welcome to the JUNGLE");
    glutDisplayFunc(display_call_back);
    glutReshapeFunc(reshape_call_back);
    glutTimerFunc(0, timer_call_back, 0);
    glutSpecialFunc(keyboard_call_back);
    //pos_x = 1, pos_y = 38;
    init_color();
    glutMainLoop();
    return 0;
}

void init_color(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    init_grid(COLUMNS, ROWS);
}

void display_call_back(){
    glClear(GL_COLOR_BUFFER_BIT);
    draw_grid();
    draw_snack();
    s_direction = 0;
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


void keyboard_call_back(int key, int, int){
    switch(key){
        case GLUT_KEY_UP:
            s_direction = UP;
            break;
        case GLUT_KEY_DOWN:
            s_direction = DOWN;
            break;
        case GLUT_KEY_LEFT:
            s_direction = LEFT;
            break;
        case GLUT_KEY_RIGHT:
            s_direction = RIGHT;
            break;
    }
}
