#include <GL/gl.h>
#include <GL/glut.h>
#include  <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include "../SOIL.h"
#include "interactionManager.hpp"

GLuint terrainList;
GLuint textureSky[5], textureWave, texureTerrain; 
double waveShift = 0.0f;
int timeLastFrame = 0;
int MAP_SIZE = 0, channels = 1, STEP_SIZE = 10;
GLubyte* heightMap;
bool bRender = true;


int height(unsigned char *pHeightMap, int X, int Y)          // This Returns The Height From A Height Map Index
{
    int x = X % MAP_SIZE;                   // Error Check Our x Value
    int y = Y % MAP_SIZE;                   // Error Check Our y Value

    if(!pHeightMap)
    {
        std::cout << "No heightMap " << std::endl;
        return 0;
    }              // Make Sure Our Data Is Valid

    return pHeightMap[x + (y * MAP_SIZE)];          // Index Into Our Height Array And Return The Height
}

void setVertexColor(unsigned char *pHeightMap, int x, int y)     // This Sets The Color Value For A Particular Index
{                               // Depending On The Height Index
    if(!pHeightMap) return;                 // Make Sure Our Height Data Is Valid

    float fColor = -0.15f + (height(pHeightMap, x, y ) / 256.0f);

    // Assign This Blue Shade To The Current Vertex
    glColor4f(0.0f, 0.0f, fColor, 1.0 );
}

void renderHeightMap(unsigned char pHeightMap[])             // This Renders The Height Map As Quads
{
    int X = 0, Y = 0;                   // Create Some Variables To Walk The Array With.
    int x, y, z;                        // Create Some Variables For Readability

    if(!pHeightMap)
    {
        std::cout << "No heightMap " << std::endl;
        return;
    }
    if(bRender)                     // What We Want To Render
        glBegin( GL_QUADS );                // Render Polygons
    else
        glBegin( GL_LINES );                // Render Lines Instead
    for ( X = 0; X < (MAP_SIZE-STEP_SIZE); X += STEP_SIZE )
        for ( Y = 0; Y < (MAP_SIZE-STEP_SIZE); Y += STEP_SIZE )
        {
            // Get The (X, Y, Z) Value For The Bottom Left Vertex
            x = X;
            y = height(pHeightMap, X, Y );
            z = Y;

            // Set The Color Value Of The Current Vertex
            setVertexColor(pHeightMap, x, z);

            glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered

            // Get The (X, Y, Z) Value For The Top Left Vertex
            x = X;
            y = height(pHeightMap, X, Y + STEP_SIZE );
            z = Y + STEP_SIZE ;

            // Set The Color Value Of The Current Vertex
            setVertexColor(pHeightMap, x, z);

            glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered

            // Get The (X, Y, Z) Value For The Top Right Vertex
            x = X + STEP_SIZE;
            y = height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE );
            z = Y + STEP_SIZE ;

            // Set The Color Value Of The Current Vertex
            setVertexColor(pHeightMap, x, z);

            glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered

            // Get The (X, Y, Z) Value For The Bottom Right Vertex
            x = X + STEP_SIZE;
            y = height(pHeightMap, X + STEP_SIZE, Y );
            z = Y;

            // Set The Color Value Of The Current Vertex
            setVertexColor(pHeightMap, x, z);

            glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered

            std::cout<<x<<","<<y<<","<<z<<std::endl;
        }
    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          // Reset The Color
}

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
                glTranslatef(0.0,0.0, (GLfloat) waveShift);
                glCallList(terrainList+1); // Waves
            glPopMatrix();

            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            glCallList(terrainList); // Sky

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glPopMatrix();


        glPushMatrix();
            glTranslatef(0,-200,50);
            //glScalef(0.5,0.5,0.5);
            /*
            glGenTextures(1, &texureTerrain);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texureTerrain);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Repeat texture
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, MAP_SIZE, MAP_SIZE, 0, GL_RED, GL_UNSIGNED_BYTE, heightMap);
            */
            renderHeightMap(heightMap);
        glPopMatrix();

    glPopMatrix();

    // Move the waves
    int timeThisFrame = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeThisFrame - timeLastFrame;
    timeLastFrame = timeThisFrame;
    waveShift = waveShift > -0.23 ? waveShift - deltaTime * 0.00005 : 0.0 ;

    glFlush();
    glutSwapBuffers();
    //glutPostRedisplay();
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

void drawSky()
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
}

void init (void) {
    glClearColor(0.7, 0.75, 0.85, 0.0); // Background color
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND); // Enable transparency on texture
    glDisable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(0.0, -30.0, 20.0, 0.0, -30.0, 50.0, 0.0, 1.0, 0.0);

    // load an image file directly as a new OpenGL texture
    textureSky[0] = loadTexture("../images/SkyBox1.bmp");
    textureSky[1] = loadTexture("../images/SkyBox4.bmp");
    textureSky[2] = loadTexture("../images/SkyBox3.bmp");
    textureSky[3] = loadTexture("../images/SkyBox2.bmp");
    textureSky[4] = loadTexture("../images/SkyBox0.bmp");
    textureWave = loadTexture("../images/wave.bmp");
    texureTerrain = loadTexture("../images/terrain-texture.bmp");

    terrainList = glGenLists(2);

    glNewList(terrainList, GL_COMPILE);
    drawSky();
    glEndList();

    glNewList(terrainList + 1, GL_COMPILE);
    drawWave();
    glEndList();

    heightMap = SOIL_load_image("../images/heightmap.bmp", &MAP_SIZE, &MAP_SIZE, &channels, SOIL_LOAD_L);
    /*
    for(int j=0; j*2 < MAP_SIZE; j++)
    {
        int index1 = j * MAP_SIZE;
        int index2 = (MAP_SIZE - 1 - j) * MAP_SIZE;
        for(int i = MAP_SIZE; i>0; i--)
        {
            GLubyte  temp = heightMap[index1];
            heightMap[index1] = heightMap[index2];
            heightMap[index2] = temp;
            index1++;
            index2++;
        }
    }*/

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