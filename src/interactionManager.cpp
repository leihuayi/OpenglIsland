//
// Created by Sarah Gross on 4/22/18
//
#include <GL/gl.h>
#include <GL/glut.h>
#include "interactionManager.hpp"
#include <iostream>
#include <glm/glm.hpp>

static int menu_id;
bool mouseDown = false;
float zoom = 10.0;
float speed = 0.0;
int CAMERA_SPEED = 0; // = 0 if the camera doesn't move, =1 is camera speed increases, =2 if camera speed decreases.
bool CAMERA_IN = true; // true for zoom in

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

void menu(int num){
    xrot =0; yrot=0;
    zoom=10.0;
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
    gluPerspective(110,1.0,1.0,1000);
    glMatrixMode (GL_MODELVIEW);

    gluLookAt(0.0, -30.0, -5.0, 0.0, -35.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP: // space bar
            CAMERA_SPEED = 1;
            CAMERA_IN = true;
            break;

        case GLUT_KEY_DOWN: // space bar
            CAMERA_SPEED = 1;
            CAMERA_IN = false;
            break;

        case GLUT_KEY_RIGHT:
            std::cout<<zoom<<std::endl;
            std::cout<<glm::sin(glm::radians(xrot)) * (zoom-10)<<std::endl;
            break;

        default:
            break;
    }
}

void keyboardUp(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP: // space bar
            CAMERA_SPEED = 2;
            break;

        case GLUT_KEY_DOWN: // space bar
            CAMERA_SPEED = 2;
            break;

        default:
            break;
    }
}

void updateCamera(void)
{

    gluLookAt(0.0, 0.0, zoom, 0.0, 0, 0, 0.0, 1.0, 0.0);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);


    if (CAMERA_SPEED != 0)
    {
        if(CAMERA_IN){
            if(glm::sin(glm::radians(xrot)) * (zoom-10) > -30 and glm::cos(glm::radians(xrot)) * (zoom-10) < 80
               and glm::sin(glm::radians(xrot)) * (zoom-10) < 60) zoom += speed;
        }
        else{
            if(zoom > 1) zoom -= speed ;
        }
        if(CAMERA_SPEED == 1)
        {
            if (speed < 1) speed += 0.02;
        }
        else
        {
            if (speed > 0) { speed -= 0.02; }
            else { CAMERA_SPEED = 0; }
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;

        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
    {
        mouseDown = false;
    }
}

// Function for rotating the pyramid with the mouse
void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        if(glm::sin(glm::radians(y + ydiff)) * (zoom-10) > -30 and glm::cos(glm::radians(y + ydiff)) * (zoom -10) < 90
                                                                   and glm::sin(glm::radians(y + ydiff)) * (zoom-10) < 60)
        {
            yrot = x - xdiff;
            xrot = y + ydiff;
        }

        glutPostRedisplay();
    }
}