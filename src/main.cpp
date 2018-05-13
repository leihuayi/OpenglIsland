#include <GL/glew.h>
#include  <iostream>

#include "interactionManager.hpp"
#include "terrain.hpp"

GLuint terrainList;
float waveShift = 0.0f;


void display(void)
{

/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateCamera();

    glPushMatrix();
            glScalef(100.0, 100.0, 100.0);

            glPushMatrix();
                glTranslatef(0.0,0.0, (GLfloat) waveShift);
                glCallList(terrainList); // Draw Waves
            glPopMatrix();

            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            glCallList(terrainList+1); // Draw Sky

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
        glCallList(terrainList + 2);
    glPopMatrix();

    waveShift = updateWaves(waveShift);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void init (void) {
    glClearColor(0.7, 0.75, 0.85, 0.0); // Background color
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND); // Enable transparency on texture
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_PLANE0);

    glLoadIdentity();

    terrainList = glGenLists(3);

    createTerrainList(terrainList);

    initCamera();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize (900, 900);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Project 2 : Terrain");
    createMenu();
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize." << std::endl;
        return 0;
    }
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}