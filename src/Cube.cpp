//
//  Cube.cpp
//

#include "Header.hpp"
#include "Geometry.hpp"
#include "Cube.hpp"

// indexes of the points for each segment
// for each segment we have 2 indexes : point1 : point2
int Cube::segmentsIndexes[CUBE_NB_SEG_PER_CUBE*2] = {
                0,1,  1,2,  2,3,  3,0,
                4,5,  5,6,  6,7,  7,4,
                0,4,  1,5,  2,6,  3,7   };


Cube::Cube() {
}

Cube::Cube(glm::dvec3 position1, glm::dvec3 rotation1, glm::dvec3 dim1) {
    centerPosition = position1;
    rotation = rotation1;
    dimension = dim1;
    updateCubePoints();
}

/*
 update the points of the cube from
 centerPosition, rotation, dimension
 */
void Cube::updateCubePoints() {

    // build the matrix to set the coords of the points
    glm::dmat4 matrix1(1.0);

    //std::cout << "updateCubePoints rotation.z " << rotation.z << " deg " << glm::degrees(rotation.z) << " rad " << glm::radians(rotation.z) << std::endl;

    //
    matrix1 = glm::translate(matrix1, centerPosition);
    // the order of the 3 rotations is important
    // this order is consistent with Blender
    matrix1 = glm::rotate(matrix1, (rotation.z), glm::dvec3(0,0,1));
    matrix1 = glm::rotate(matrix1, (rotation.y), glm::dvec3(0,1,0));
    matrix1 = glm::rotate(matrix1, (rotation.x), glm::dvec3(1,0,0));

    // points of the corners of the cube
    int index = 0;
    glm::dvec3 dim1 = dimension;
    points[index++] = glm::dvec3(-dim1.x/2,+dim1.y/2,+dim1.z/2); // 0
    points[index++] = glm::dvec3(+dim1.x/2,+dim1.y/2,+dim1.z/2); // 1
    points[index++] = glm::dvec3(+dim1.x/2,-dim1.y/2,+dim1.z/2); // 2
    points[index++] = glm::dvec3(-dim1.x/2,-dim1.y/2,+dim1.z/2); // 3
    points[index++] = glm::dvec3(-dim1.x/2,+dim1.y/2,-dim1.z/2); // 4
    points[index++] = glm::dvec3(+dim1.x/2,+dim1.y/2,-dim1.z/2); // 5
    points[index++] = glm::dvec3(+dim1.x/2,-dim1.y/2,-dim1.z/2); // 6
    points[index++] = glm::dvec3(-dim1.x/2,-dim1.y/2,-dim1.z/2); // 7
    
    
    // loop to apply the matrix on the points
    for (int index1=0; index1 < CUBE_NB_POINTS; index1++) {
        points[index1] = glm::dvec3( (matrix1 * glm::vec4(points[index1],1.0f)) );
    }
    
}

/*
 get the inverse matrix to put the cube in position 0,0,0 and rotation 0,0,0
 */
glm::dmat4 Cube::getCubeInvMatrix() {
    glm::dmat4 matrixInv1(1.0);
    // the order is important: it is consistent with Blender
    matrixInv1 = glm::rotate(matrixInv1, -rotation.x, glm::dvec3(1,0,0));
    matrixInv1 = glm::rotate(matrixInv1, -rotation.y, glm::dvec3(0,1,0));
    matrixInv1 = glm::rotate(matrixInv1, -rotation.z, glm::dvec3(0,0,1));
    matrixInv1 = glm::translate(matrixInv1, -centerPosition);
    return matrixInv1;
}

// return false if no intersection
bool Cube::isIntersectingWithCube2(Cube cube2) {
    
    // test if distance < (dimension/2)
    double dim1 = glm::length(dimension) / 2;
    double dim2 = glm::length(cube2.dimension) / 2;
    double dist1 = glm::length( cube2.centerPosition - centerPosition );
    //std::cout << "isIntersectingWithCube2 dist1 " << dist1 << " dim1 " << dim1 << " dim2 " << dim2 << std::endl;
    if (dist1 > (dim1 + dim2)) {
        // too much distance between the 2 cubes , don't interseect
        std::cout << "isIntersectingWithCube2 : FALSE : cubes don't intersect too much distance " << std::endl;
        return false;
    }
    
    // move the points of Cube2 with matrix inverse of Cube1
    // check if Cube2 has 1 point inside Cube1
    glm::dmat4 matrixInv1 = getCubeInvMatrix();
    glm::dvec3 points2_to_c1[CUBE_NB_POINTS];
    for (int index1=0; index1 < CUBE_NB_POINTS; index1++) {
        glm::dvec3 pt2 = cube2.points[index1];
        glm::dvec3 pt2_2 = glm::dvec3( matrixInv1 * glm::vec4(pt2,1.0f) );
        points2_to_c1[index1] = pt2_2;
        if (Geometry::isPointInsideDimension(pt2_2, dimension)) {
            std::cout << "isIntersectingWithCube2 : TRUE : cube2 point inside cube1 " << std::endl;
            return true;
        }
    }
    //Geometry::displayLines("C2toC1-", points2_to_c1[0], points2_to_c1[1], points2_to_c1[2], points2_to_c1[3] );

    // move the points of Cube1 with matrix inverse of Cube2
    // check if Cube1 has 1 point inside Cube2
    glm::dmat4 matrixInv2 = cube2.getCubeInvMatrix();
    glm::dvec3 points1_to_c2[CUBE_NB_POINTS];
    for (int index1=0; index1 < CUBE_NB_POINTS; index1++) {
        glm::dvec3 pt1 = points[index1];
        glm::dvec3 pt1_2 = glm::dvec3( matrixInv2 * glm::vec4(pt1,1.0f) );
        points1_to_c2[index1] = pt1_2;
        if (Geometry::isPointInsideDimension(pt1_2, cube2.dimension)) {
            std::cout << "isIntersectingWithCube2 : TRUE : cube1 point inside cube2 " << std::endl;
            return true;
        }
    }
    
    // check if Cube2 has 1 segment intersecting Cube1
    for (int index1=0; index1 < CUBE_NB_SEG_PER_CUBE; index1++) {
        int ixP1 = cube2.segmentsIndexes[2*index1+0];
        int ixP2 = cube2.segmentsIndexes[2*index1+1];
        glm::dvec3 pt1 = points2_to_c1[ixP1];
        glm::dvec3 pt2 = points2_to_c1[ixP2];
        if (Geometry::isSegmentInsideDimension(pt1,pt2, dimension) ) {
            std::cout << "isIntersectingWithCube2 : TRUE : cube2 segment inside cube1 " << std::endl;
            return true;
        }
    }
    
    // check if Cube1 has 1 segment intersecting Cube2
    for (int index1=0; index1 < CUBE_NB_SEG_PER_CUBE; index1++) {
        int ixP1 = this->segmentsIndexes[2*index1+0];
        int ixP2 = this->segmentsIndexes[2*index1+1];
        glm::dvec3 pt1 = points1_to_c2[ixP1];
        glm::dvec3 pt2 = points1_to_c2[ixP2];
        if (Geometry::isSegmentInsideDimension(pt1,pt2, cube2.dimension) ) {
            std::cout << "isIntersectingWithCube2 : TRUE : cube1 segment inside cube2 " << std::endl;
            return true;
        }
    }
    
    //
    std::cout << "isIntersectingWithCube2 : FALSE : no intersection " << std::endl;
    return false;
}

/*
 for testing purpose : to display lines in blender
 */
void Cube::displayCubeLines(std::string prefix) {
    // trace
    Geometry::displayLines(prefix, points[0], points[1], points[2], points[3]);
    Geometry::displayLines(prefix, points[4], points[5], points[6], points[7]);
}

/*
 for testing purpose : 
 read cubes from blender from a text file
 see blender script : Save-Cubes-02.py
 */
std::vector<Cube> Cube::readCubes() {
    std::vector<Cube> cubes;

    const char *homeDir = getenv("HOME");
    std::string pathname = homeDir;
    pathname = pathname + "/Downloads/cubes-01.txt";
    std::ifstream file1(pathname);
    if (!file1.is_open()) {
        std::cout << "Open file error: " << pathname << std::endl;
        return cubes;
    }
    
    Cube cube1;
    
    std::string line1;
    while (std::getline(file1, line1)) {
        std::istringstream iss(line1);
        std::string word1;
        std::getline(iss, word1, ',');
        std::cout << "Name: " << word1;
        std::getline(iss, word1, ',');
        cube1.centerPosition.x = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.centerPosition.y = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.centerPosition.z = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.rotation.x = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.rotation.y = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.rotation.z = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.dimension.x = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.dimension.y = std::atof(word1.c_str());
        std::getline(iss, word1, ',');
        cube1.dimension.z = std::atof(word1.c_str());
        std::cout << " Pos: " << cube1.centerPosition.x << " " << cube1.centerPosition.y << " " << cube1.centerPosition.z;
        std::cout << " Rot: " << glm::degrees(cube1.rotation.x) << " " << glm::degrees(cube1.rotation.y) << " " << glm::degrees(cube1.rotation.z);
        std::cout << " Dim: " << cube1.dimension.x << " " << cube1.dimension.y << " " << cube1.dimension.z << std::endl;
        cube1.updateCubePoints();
        cubes.push_back(cube1);
    }
    
    return cubes;
}
