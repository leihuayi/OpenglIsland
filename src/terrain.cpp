//
// Created by Sarah Gross on 5/7/18
//

#include "terrain.hpp"
#include <iostream>

void drawWave(GLuint textureWave)
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

void drawSky(GLuint textureSky[])
{
    glColor4f(1.0,1.0,1.0,0.5);

    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, textureSky[1]);
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
    int X = 0, Y = 0;                   // Create Some Variables To Walk The Array With.
    int x, y, z;                        // Create Some Variables For Readability

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
            float y1 = j * size;
            float x2 = (i + 1) * size;
            float y2 = (j + 1) * size;

            glMultiTexCoord2f(GL_TEXTURE0, j * step, i * step);
            glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
            glVertex3f(x1, height1, y1);

            glMultiTexCoord2f(GL_TEXTURE0, j * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
            glVertex3f(x2, height3, y1);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
            glVertex3f(x2, height4, y2);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, i * step);
            glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
            glVertex3f(x1, height2, y2);
        }
    }

    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          // Reset The Color
}
