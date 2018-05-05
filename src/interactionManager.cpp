//
// Created by Sarah Gross on 4/22/18
//
#include <GL/gl.h>
#include <GL/glut.h>
#include "interactionManager.hpp"

static int menu_id;
bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

void menu(int num){
    xrot =0; yrot=0;
    glutPostRedisplay();
}

void createMenu(void){
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Reset camera",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(110,1.0,1.0,200);
    glMatrixMode (GL_MODELVIEW);
}

/*
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 32: // space bar
            break;

        default:
            break;
    }
}*/

// Function for rotating the pyramid with the mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;

        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

// Function for rotating the pyramid with the mouse
void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}