#include <GL/gl.h>
#include <GL/glut.h>
#include  <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include "../SOIL.h"
#include "interactionManager.hpp"
#include "terrain.hpp"

GLuint terrainList;
GLuint textureSky[5], textureWave, textureTerrain[2];
float waveShift = 0.0f;
GLubyte* heightMap;

void display(void)
{

/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        updateCameraSpeed();
        gluLookAt(0.0, 0.0, zoom, 0.0, -30.0, zoom+20, 0.0, 1.0, 0.0);
        glRotatef(xrot, 1.0f, 0.0f, 0.0f);
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
            glScalef(100.0, 100.0, 100.0);

            glPushMatrix();
                glTranslatef(0.0,0.0, (GLfloat) waveShift);
                glCallList(terrainList+1); // Draw Waves
            glPopMatrix();

            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            glCallList(terrainList); // Draw Sky

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glPopMatrix();

        glPushMatrix();

            glCallList(terrainList + 2);
        glPopMatrix();
    glPopMatrix();

    waveShift = updateWaves(waveShift);

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

void init (void) {
    glClearColor(0.7, 0.75, 0.85, 0.0); // Background color
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND); // Enable transparency on texture
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);   // Enable Texture Mapping
    glEnable(GL_CLIP_PLANE0);

    glutIgnoreKeyRepeat(true);

    glLoadIdentity();

    // load an image file directly as a new OpenGL texture
    textureSky[0] = loadTexture("../images/SkyBox1.bmp");
    textureSky[1] = loadTexture("../images/SkyBox4.bmp");
    textureSky[2] = loadTexture("../images/SkyBox3.bmp");
    textureSky[3] = loadTexture("../images/SkyBox2.bmp");
    textureSky[4] = loadTexture("../images/SkyBox0.bmp");
    textureWave = loadTexture("../images/wave.bmp");
    textureTerrain[0] = loadTexture("../images/terrain-texture.bmp");
    textureTerrain[1] = loadTexture("../images/terrain-detail.bmp");
    int MAP_SIZE = 0, channels = 1;
    heightMap = SOIL_load_image("../images/heightmap.bmp", &MAP_SIZE, &MAP_SIZE, &channels, SOIL_LOAD_L);

    terrainList = glGenLists(3);

    glNewList(terrainList, GL_COMPILE);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        drawSky(textureSky);
        glDisable(GL_TEXTURE_2D);
    glEndList();

    glNewList(terrainList + 1, GL_COMPILE);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        drawWaves(textureWave);
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLdouble plane[4] = {0.0,1,0.0,-7};

    glNewList(terrainList + 2, GL_COMPILE);
        glTranslatef(-10,-57,-10);
        glScalef(0.5,0.5,0.5);
        glClipPlane(GL_CLIP_PLANE0, plane);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureTerrain[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureTerrain[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD_SIGNED);

        drawTerrain(heightMap, MAP_SIZE);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_2D);
    glEndList();

    gluLookAt(0.0, 0.0, 30.0, 0.0, -30.0, 50.0, 0.0, 1.0, 0.0);
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
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}