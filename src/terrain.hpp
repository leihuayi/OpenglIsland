//
// Created by Sarah Gross on 5/7/18
//

#ifndef TERRAIN_TERRAIN_H
#define TERRAIN_TERRAIN_H

#endif //TERRAIN_TERRAIN_H

#include <GL/gl.h>
#include <GL/glut.h>

void drawWaves(GLuint textureWave);
float updateWaves(float waveshift);
void drawSky(GLuint textureSky[]);
void drawTerrain(GLubyte* heightMap, int map_size);