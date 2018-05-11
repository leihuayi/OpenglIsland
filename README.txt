README
Author: Sarah Gross <leihy17@mails.tsinghua.edu.cn>, student 2017280160

---------------------------------------------------------------------------
Overview
---------------------------------------------------------------------------

This project renders an animation of a Terrain

demo.mp4 shows a demonstration of the result 

---------------------------------------------------------------------------
Building and running the Code
---------------------------------------------------------------------------

This project was originally built using the IDE CLion using CMakeLists.txt.
The file cmake/FindSOIL.cmake gives information on the SOIL lib so that the
program can build successfully.

Linux
-------------------------
Download Cmake :
https://askubuntu.com/questions/829310/how-to-upgrade-cmake-in-ubuntu/829311

Create a new folder "build" at the root :
    mkdir build
    cd build
    cmake ..
    make


To run the program, go to build folder and run :
    ./Terrain


Windows
-------------------------
Download Cmake (https://cmake.org/download/)
Follow this tutorial to build and run the code :
https://cmake.org/runningcmake/


---------------------------------------------------------------------------
Source Files and Directory Structure
---------------------------------------------------------------------------

The code is in the src folder.


README              -- this file
CMakeLists          -- info for building the code
demo.mp4            -- video demonstration
SOIL.h              -- library SOIL

cmake/              -- extra libraries loading

src/                == Project-specific files.
    main            -- contains main function for project : init of opengl
    terrain		-- all functions for drawing the terrain : draw waves and sky
    interactionManager -- all functions related to user input : rotation of
                           the view, show menu, update view


---------------------------------------------------------------------------
Bonus
---------------------------------------------------------------------------

1- I created a background using 6 planes instead of a skybox, in order to use
    it for the next project.
2- There are interactions available with the mouse : drag to rotate the view,
    right click to display a menu.


---------------------------------------------------------------------------
Implementation details
--------------------------------------------------------------------------
- I decided to use 2 display lists, one for loading the background (create the 6 planes
    and bind the texture to them), the second for the wave.

