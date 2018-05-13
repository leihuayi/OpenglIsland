//
// Created by Sarah Gross on 4/22/18
//
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>

#include "interactionManager.hpp"
#include "camera.hpp"
using namespace glm;

static int menu_id;
bool mouseDown = false;
float zoom = 10.0;
float speed = 0.0;
int CAMERA_SPEED = 0; // = 0 if the camera doesn't move, =1 is camera speed increases, =2 if camera speed decreases.
bool CAMERA_IN = true; // true for zoom in
Camera camera;

class Window {
public:
    Window() {
        this->interval = 1000 / 60;		//60 FPS
        this->window_handle = -1;
    }
    int window_handle, interval;
    ivec2 size;
    float window_aspect;
} window;


void menu(int num){
    camera.SetPosition(glm::vec3(-10, -30, -10));
    camera.SetLookAt(glm::vec3(0, -35, 0));
    glutPostRedisplay();
}

void createMenu(void){
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Reset camera",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h)
{
    if (h > 0) {
        window.size = ivec2(w, h);
        window.window_aspect = float(w) / float(h);
    }
    camera.SetViewport(0, 0, window.size.x, window.size.y);
}

bool check_dir(int i, int j)
{
    return camera.camera_position[i]*camera.camera_direction[j]<0;
}

void keyboard(int key, int x, int y)
{
    bool check_pos_x = abs(camera.camera_position.x)<90;
    bool check_pos_y = abs(camera.camera_position.y+5)<40;
    bool check_pos_z = abs(camera.camera_position.z)<90;

    switch(key)
    {
        case GLUT_KEY_UP:
            if ((check_pos_x or check_dir(0,0)) and (check_pos_y or check_dir(1,1)) and (check_pos_z or check_dir(2,2)))
            {camera.Move(FORWARD);}
            break;
        case  GLUT_KEY_LEFT:
            if((check_pos_x or check_dir(0,2)) and (check_pos_z or !check_dir(2,0)))
            {camera.Move(LEFT);}
            break;
        case GLUT_KEY_DOWN:
            if ((check_pos_x or !check_dir(0,0)) and (check_pos_y or !check_dir(1,1)) and (check_pos_z or !check_dir(2,2)))
            {camera.Move(BACK);}
            break;
        case  GLUT_KEY_RIGHT:
            if((check_pos_x or !check_dir(0,2)) and (check_pos_z or check_dir(2,0)))
            {camera.Move(RIGHT);}
            break;

        default:
            break;
    }
}

void updateCamera(void)
{
    glm::mat4 model, view, projection;
    camera.Update();
    camera.GetMatricies(projection, view, model);

    glm::mat4 mvp = projection* view * model;	//Compute the mvp matrix
    glLoadMatrixf(glm::value_ptr(mvp));
}

void mouse(int button, int state, int x, int y)
{
    camera.SetPos(button, state, x, y);
}

// Function for rotating the pyramid with the mouse
void mouseMotion(int x, int y)
{
    camera.Move2D(x, y);
}

void initCamera()
{
    camera.SetMode(FREE);
    camera.SetPosition(glm::vec3(-10, -30, -10));
    camera.SetLookAt(glm::vec3(0, -35, 0));
    camera.SetClipping(.1, 1000);
    camera.SetFOV(50);
}