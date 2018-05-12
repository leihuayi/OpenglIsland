//
// Created by Sarah Gross on 5/7/18
//

#include "terrain.hpp"
#include "../SOIL.h"
#include <iostream>

int timeLastFrame = 0;
GLuint textureSky[6], textureWave, textureTerrain[2];

GLubyte* heightMap;

void drawWaves()
{
    glColor4f(0.7,0.9,1.0,1.0);

    glBindTexture(GL_TEXTURE_2D, textureWave);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(10.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(10.0f, 10.0f); glVertex3f(-1.0f, -0.5f,  1.3f);  // Bottom Right Of The Texture and Quad
    glEnd();
}

float updateWaves(float waveShift)
{
    // Move the waves
    int timeThisFrame = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeThisFrame - timeLastFrame;
    timeLastFrame = timeThisFrame;
    waveShift = waveShift > -0.23 ? waveShift - deltaTime * 0.00005 : 0.0;
    return waveShift;
}

void drawSky()
{
    glColor4f(1.0,1.0,1.0,0.5);

    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, textureSky[5]);
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

    // Top Face
    glBindTexture(GL_TEXTURE_2D, textureSky[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glEnd();

    // Front
    glBindTexture(GL_TEXTURE_2D, textureSky[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    // Back Face
    glBindTexture(GL_TEXTURE_2D, textureSky[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, textureSky[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.5f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.5f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Right Face
    glBindTexture(GL_TEXTURE_2D, textureSky[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.5f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.5f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();
}

void drawTerrain(unsigned char pHeightMap[], int map_size)             // This Renders The Height Map As Quads
{
    if(!pHeightMap)
    {
        std::cout << "No heightMap " << std::endl;
        return;
    }

    glBegin(GL_QUADS);

    float size = 0.5f;
    float scale = 0.1f; // Scale : rescale the terrain in height
    float step = 1.0f / (map_size - 1);
    for (int i = 0; i < map_size - 1; ++i)  {
        for (int j = 0; j < map_size - 1; ++j)  {
            float height1 = pHeightMap[i * map_size + j] * scale;
            float height2 = pHeightMap[i * map_size + j + 1] * scale;
            float height3 = pHeightMap[(i + 1) * map_size + j] * scale;
            float height4 = pHeightMap[(i + 1) * map_size + j + 1] * scale;
            float x1 = i * size;
            float z1 = j * size;
            float x2 = (i + 1) * size;
            float z2 = (j + 1) * size;

            glMultiTexCoord2f(GL_TEXTURE0, j * step, i * step);
            glMultiTexCoord2f(GL_TEXTURE1, j * step, i * step);
            glVertex3f(x1, height1, z1);

            glMultiTexCoord2f(GL_TEXTURE0, j * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, j * step, (i + 1) * step);
            glVertex3f(x2, height3, z1);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, (j + 1) * step, (i + 1) * step);
            glVertex3f(x2, height4, z2);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, i * step);
            glMultiTexCoord2f(GL_TEXTURE1, (j + 1) * step, i * step);
            glVertex3f(x1, height2, z2);
        }
    }

    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          // Reset The Color
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

void createTerrainList(GLuint list)
{
    // load an image file directly as a new OpenGL texture
    textureSky[0] = loadTexture("../images/SkyBox1.bmp");
    textureSky[1] = loadTexture("../images/SkyBox4.bmp");
    textureSky[2] = loadTexture("../images/SkyBox3.bmp");
    textureSky[3] = loadTexture("../images/SkyBox2.bmp");
    textureSky[4] = loadTexture("../images/SkyBox0.bmp");
    textureSky[5] = loadTexture("../images/SkyBoxReflect.png");
    textureWave = loadTexture("../images/wave.bmp");
    textureTerrain[0] = loadTexture("../images/terrain-texture.bmp");
    textureTerrain[1] = loadTexture("../images/terrain-detail.bmp");
    int MAP_SIZE = 0, channels = 1;
    heightMap = SOIL_load_image("../images/heightmap.bmp", &MAP_SIZE, &MAP_SIZE, &channels, SOIL_LOAD_L);


    glNewList(list, GL_COMPILE);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        drawWaves();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    glNewList(list + 1, GL_COMPILE);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        drawSky();
        glDisable(GL_TEXTURE_2D);
    glEndList();

    GLdouble plane[4] = {0.0,1,0.0,-7};

    glNewList(list + 2, GL_COMPILE);
        glTranslatef(0,-57,0);
        glScalef(0.3,0.3,0.3);
        glClipPlane(GL_CLIP_PLANE0, plane);

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureTerrain[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureTerrain[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD_SIGNED);

        drawTerrain(heightMap, MAP_SIZE);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_2D);
    glEndList();
}
