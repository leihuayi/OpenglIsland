README
Author: Sarah Gross

# Overview

This project renders a island created from a heightmap with flowing water
around.

demo.gif shows a demonstration of the result.
![alt text](https://github.com/Akahime/OpenglIsland/blob/master/demo.gif)

# Building and running the Code

This project was originally built using the IDE CLion using CMakeLists.txt.
The file cmake/FindSOIL.cmake gives information on the SOIL lib so that the
program can build successfully.

## Linux

Download Cmake :
https://askubuntu.com/questions/829310/how-to-upgrade-cmake-in-ubuntu/829311

Create a new folder "build" at the root :

    mkdir build
    cd build
    cmake ..
    make


To run the program, go to build folder and run :
    `./Terrain`


## Windows

Download Cmake (https://cmake.org/download/)
Follow this tutorial to build and run the code :
https://cmake.org/runningcmake/


# Source Files and Directory Structure


The code is in the src folder.


README              -- this file
CMakeLists          -- info for building the code
demo.mp4            -- video demonstration
SOIL.h              -- library SOIL

cmake/              -- extra libraries loading

src/                == Project-specific files.
    main            -- contains main function for project : init of opengl,
                        creation of displaylists
    terrain         -- all functions for drawing the terrain : sky, waves,
                        and terrain generation, movement of waves,
                        displaylists content with textures
    interactionManager -- all functions related to user input : rotation of
                           the view, show menu, update view


# Implementation steps


1. I built the skybox using 5 planes (terrain.cpp/drawSky() ). The base is
    a square between coordinates (-1,1), the height is between (-0.5,0.5)
    since the original images are stretched.

2. I added a 6th bottom plane to the skybox, which is the reflection of the
    top plane. I created a new function in terrain.cpp call drawWaves() which
    adds a plane with water texture on the reflected sky plane.

3. I made the waves move.
    I created the waves plane a big longer than the bottom plane and make
    it move forward by translating it of value "waveShift" in z direction before
    drawing it. If I didn't make the plane longer, the user would see the waves
    texture disappear at the end of the ocean.
    I update wavesShift value in terrain.cpp/updateWaves() function.
    In order to keep the water flowing eternally, I reset waveShift value when
    it has reached the repetition value of the texture.

    How did I find this value ?
    I set that the wave texture would repeat 10 times in the plane (when I create
    the waves, I set glTexCoord2f(0.0f, 10.0f)). Let x the length I need to add
    to my waves plane so that I can reset its position without the user seeing it.
    The plane length is between (-1, 1+x) so it is 2+x long.
    It is divided in 10 times the same texture so each texture fragment has a length
    of 0.2 + 0.1x.
    We want 0.2 + 0.1x < x so that we don't see the end of the wave plane before
    we reset the wave plane position. This gives x > 0.22.
    So I chose an x = 0.3 which is why I wrote z=1.3f for two wave plane vertices.
    I need to reset the wave plane position when waveShift is as big as one texture
    fragment = 0.2 + 0.1x = 0.23 hence the condition waveShift > -0.23.

    Finally, in order not that the see the wave plane is bigger than the bottom plane
    through the walls of the skyBox, I chose a blending value :
    `glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);`
    between drawing the waves and drawing the sky.

4. I drew the terrain by first loading the heightmap using SOIL library, then I used the
    function terrain.cpp/drawTerrain() to loop through the heightMap array and build in each
    loop a quad (4 vertices) by reading for each x, z value its corresponding height, using
    the formula :
        height for point (x, z) = heightmap[x][z] = heightmap[x * sizemap + z]
    because heightmap is actually a one-dimension array of size (sizemap * sizemap) instead
    of a matrix size sizemap x sizemap.
    We resize the height using the value scale, since otherwise the terrain height variance
    would we way too big and look strange.

5. Since using blending functions to see the water through the terrain would be complicated
    given that we already have a blending constraint on the sky - water couple, I decided to
    use a clipping plane for that purpose.

    Our skybox is originally between y (-0.5,+0.5). We scale this by 100 so now it is between
    (-50,+50). Since the water plane is superposed on the bottom of the skybox, it is on the
     plane of coordinate y=-50.
     Therefore I put the terrain slightly below, on the plane y = -57 so that the water gets
     above the lowest points of the terrain. Then I created a clipping plane of normal
     (0,1,0) cutting everything beneath -7, since originally the terrain is centered on plane
     y=0.
     I enabled the depth test in order to see better the effects of these settings while
     making these arrangements.

6. I added level detail by superposing the two terrain textures with GL_TEXTURE0 and GL_TEXTURE1.

7. In order to optimize the rendering, I put the drawing of the 3 terrain elements (skybox, wave,
    terrain) in 3 display lists. There are initialized from terrain.cpp/createTerrainList() where
    we load all the textures and create all the display lists.

8. I implemented the interactions in interactionManager.cpp, using a helper class Camera.
    The user can move around in the scene using up and back arrows to go forward and backward,
    and right and left arrowd to go right or left.

    At each frame, we compute the view and projection matrix using Camera::Update.
    In order to have smooth transitions, we slowly increase or decrease the camera rotation
    (camera_pitch) and camera movement (camera_heading).

    In interactionManager.cpp, I made many conditions on camera_position and camera_direction
    in order to avoid getting out of the box (conditions on camera_position) without staying blocked
    once we reached the box boundaries (conditions on camera_position * camera_direction).

# Remarks

* The skybox has an odd rendering as the corners are pretty obvious. Hovever, as I used the same
    skybox code for the previous homework (snow animation) and the skybox looked perfect, I
    think the problem does not come from my code but from the Skybox images given with the project.

* Since the skybox bottom was not designed as part of the skybox, it also creates a hard edge. In
    order to have a better effect, instead of plainly using the top plane reflexion, I aggregated
    all the planes that form the skybox using an image editor software to create SkyBoxReflect.png.
    This gives softer edges to the skybox where the ocean starts.