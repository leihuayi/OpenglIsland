#include <GL/gl.h>
#include <GL/glut.h>
#include  <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include "../SOIL.h"
#include "interactionManager.hpp"

GLuint textureList;
GLuint texSnow;
GLuint cubemap[6];
float waveShift = 0.0f;
int timeLastFrame = 0;

void display(void)
{

/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

        glRotatef(xrot, 1.0f, 0.0f, 0.0f);
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);

        glPushMatrix();

            glScalef(100.0, 100.0, 100.0);

            glPushMatrix();
                glTranslatef(0.0,0.0,waveShift);
                glCallList(textureList+1); // Waves
            glPopMatrix();

            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            glCallList(textureList); // skybox

        glPopMatrix();

    glPopMatrix();

    int timeThisFrame = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeThisFrame - timeLastFrame;
    timeLastFrame = timeThisFrame;
    waveShift -= deltaTime * 0.00005;

    if(waveShift < -0.23)
    {
        waveShift = 0;
    }

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

GLuint loadTexture( char* texName)
{
    // load an image file directly as a new OpenGL texture
    GLuint texId = SOIL_load_OGL_texture
            (
                    texName,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
            );

    // check for an error during the load process
    if( 0 == texId ) std::cout << "SOIL loading error: "<< SOIL_last_result() << std::endl;
    return texId;
}

void drawWave()
{
    glColor4f(0.7,0.9,1.0,1.0);

    glBindTexture(GL_TEXTURE_2D, cubemap[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(10.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(10.0f, 10.0f); glVertex3f(-1.0f, -0.5f,  1.3f);  // Bottom Right Of The Texture and Quad
    glEnd();
}

void drawSky()
{
    glColor4f(1.0,1.0,1.0,0.5);

    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, cubemap[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Repeat texture
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glEnd();

    glBlendFunc(GL_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0,1.0,1.0,1.0);

    // Front
    glBindTexture(GL_TEXTURE_2D, cubemap[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    // Back Face
    glBindTexture(GL_TEXTURE_2D, cubemap[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, cubemap[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Right Face
    glBindTexture(GL_TEXTURE_2D, cubemap[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    // Top Face
    glBindTexture(GL_TEXTURE_2D, cubemap[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glEnd();
}

void init (void) {
    glClearColor(0.7, 0.75, 0.85, 0.0); // Background color
    glClearDepth(1.0);

    glEnable(GL_BLEND); // Enable transparency on texture
    glDisable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(0.0, -30.0, 20.0, 0.0, -30.0, 50.0, 0.0, 1.0, 0.0);

    // load an image file directly as a new OpenGL texture
    cubemap[0] = loadTexture("../images/wave.bmp");
    cubemap[1] = loadTexture("../images/SkyBox1.bmp");
    cubemap[2] = loadTexture("../images/SkyBox4.bmp");
    cubemap[3] = loadTexture("../images/SkyBox3.bmp");
    cubemap[4] = loadTexture("../images/SkyBox2.bmp");
    cubemap[5] = loadTexture("../images/SkyBox0.bmp");

    textureList = glGenLists(2);

    glNewList(textureList, GL_COMPILE);
    drawSky();
    glEndList();

    glNewList(textureList + 1, GL_COMPILE);
    drawWave();
    glEndList();

    glEnable(GL_TEXTURE_2D);   // Enable Texture Mapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize (900, 900);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Project 2 : Terrain");
    createMenu();
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}