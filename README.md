# cubes_intersection
c++ intersection of 2 arbitrary 3D cubes

The purpose is to test if two arbitrary 3D cubes intersect.<br />
We only get TRUE or FALSE.<br />

Blender 4.1 is used to test this code.<br />
The Blender script Save-Cubes-02.py , saves the cubes (name,position,rotation,dimension) in a text file.<br />
Then the code read the text file to get (position,rotation,dimension) of the cubes and check if they intersect.<br />

The cubes have a dimension in X,Y,Z, so it can be a 3D rectangle.

We use GLM for the 3D and matrix operations.

Develop on MACOS 14.5 and with XCode 15.4

# Algorithm

1- we test if the distance between Cube1 and Cube2 is greater than the dimensions:<br />
    if YES then return FALSE : no intersection<br />
    
2- we move Cube2 with InverseMatrix of Cube1 : <br />
so that we can compare Cube2 with Cube1 when Cube1 is in position 0,0,0 and rotation 0,0,0<br />
    (this way it is easier and faster to test)<br />
    
3- test if one of the points of Cube2 is inside Cube1<br />
    if YES then return TRUE : intersection<br />
    
4- test if one the segments (edges) of Cube2 go through Cube1<br />
    if YES then return TRUE : intersection<br />
    
5- we move Cube1 with InverseMatrix of Cube2 : <br />
so that we can compare Cube1 with Cube2 when Cube2 is in position 0,0,0 and rotation 0,0,0<br />
    (this way it is easier and faster to test)<br />
    
6- test if one of the points of Cube1 is inside Cube2<br />
    if YES then return TRUE : intersection<br />
    
7- test if one the segments (edges) of Cube1 go through Cube2<br />
    if YES then return TRUE : intersection<br />    

I think this method covers all the cases.<br />

# Compile / Link

These sources have only been compiled and tested on Macos 14.5.<br />
On Windows , probably , the only difference is GLM, how to download GLM on Windows.<br />

There is a Makefile included.<br />
These sources are pretty simple to compile / link. <br />
We only use GLM (1.0.1) which are just include files, it is not a library to link.<br />
On MacOs we use homebrew to download GLM:<br />
https://formulae.brew.sh/formula/glm<br />
The download folder on Macos for GLM is : /opt/homebrew/Cellar/glm<br />


# Test Environment

We use Blender 4.1 to set 2 cubes in different test position / intersection, in the 3D view of Blender

The script window allows to save the position of the cubes in a text file , with the blender script Save-Cubes-02.py

Then we execcute the code which read the text file containing the position, rotation, dimension of the cubes, and check the intersection.

![Alt text](images/test-02.jpg?raw=true "Test setting")

# Description

![Alt text](images/cubes-3.jpg?raw=true "Position")

![Alt text](images/cubes-2.jpg?raw=true "Position")

# Tests

## Case 1 : No intersection

![Alt text](images/case1-02.png?raw=true "Test")

![Alt text](images/case1-01.png?raw=true "Test")

## Case 2 : One point of one cube inside the other cube

![Alt text](images/case2-01.png?raw=true "Test")

![Alt text](images/case2-02.png?raw=true "Test")

## Case 3 : No point inside the other cube, but one segment intersecting the other cube

![Alt text](images/case4-01.png?raw=true "Test")

![Alt text](images/case4-02.png?raw=true "Test")

## Case 4 : The 2 cubes are touching each other
When some corner points are at the same position, we consider there is intersection.<br />
See tests made in the method Geometry::isPointInsideDimension <br />

![Alt text](images/case5-01.png?raw=true "Test")

![Alt text](images/case5-02.png?raw=true "Test")
