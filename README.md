# cubes_intersection
c++ intersection of 2 arbitrary cubes

The purpose is to test if two arbitrary 3D cubes intersect.
We only get TRUE or FALSE.

Blender is used to test this code.
The script Save-Cubes-02.py save the cubes (name,position,rotation,dimension) in a text file.
Then the code read the text file to test if the 2 cubes intersect.

The cubes have a dimension in X,Y,Z, so it can be a 3D rectangle.

We use GLM for the 3D and matrix operations.

Develop on MACOS 14.5 and with XCode 15.4

We method is as following:
1- we test if the distance between Cube2 and Cube1 is greater than the dimensions:
    if YES then return FALSE no intersection
2- we move Cube2 so that Cube1 is in position 0,0,0 and rotation 0,0,0
3- 
