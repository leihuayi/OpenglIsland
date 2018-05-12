//
// Created by Sarah Gross on 5/7/18
//

#ifndef TERRAIN_TERRAIN_H
#define TERRAIN_TERRAIN_H

#endif //TERRAIN_TERRAIN_H

#include <GL/gl.h>
#include <GL/glut.h>

void drawWaves();
float updateWaves(float waveshift);
void drawSky();
void drawTerrain(GLubyte* heightMap, int map_size);
void createTerrainList(GLuint list);