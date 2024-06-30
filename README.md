# cubes_intersection
c++ intersection of 2 arbitrary 3D cubes

The purpose is to test if two arbitrary 3D cubes intersect.<br />
We only get TRUE or FALSE.<br />

Blender is used to test this code.<br />
The Blender script Save-Cubes-02.py , saves the cubes (name,position,rotation,dimension) in a text file.<br />
Then the code read the text file to get (position,rotation,dimension) of the cubes and check if they intersect.<br />

The cubes have a dimension in X,Y,Z, so it can be a 3D rectangle.

We use GLM for the 3D and matrix operations.

Develop on MACOS 14.5 and with XCode 15.4

The algorithm is :<br />
1- we test if the distance between Cube1 and Cube2 is greater than the dimensions:<br />
    if YES then return FALSE : no intersection<br />
2- we move Cube2 so that Cube1 is in position 0,0,0 and rotation 0,0,0<br />
    (this way it is easier and faster to test)<br />
3- test if one of the points of Cube2 is inside Cube1<br />
    if YES then return TRUE : intersection<br />
4- test if one the segments of Cube2 go through Cube1<br />
    if YES then return TRUE : intersection<br />
5- we move Cube1 so that Cube2 is in position 0,0,0 and rotation 0,0,0<br />
    (this way it is easier and faster to test)<br />
6- test if one of the points of Cube1 is inside Cube2<br />
    if YES then return TRUE : intersection<br />
7- test if one the segments of Cube1 go through Cube2<br />
    if YES then return TRUE : intersection<br />    

I think this method covers all the cases.<br />



