//
//  Cube.hpp
//  
//

#ifndef Cube_hpp
#define Cube_hpp

#define CUBE_NB_SEG_PER_CUBE 12
#define CUBE_NB_POINTS 8

class Cube {
public:
    Cube();
    Cube(glm::dvec3 position, glm::dvec3 rotation, glm::dvec3 dim1);
public:
    glm::dvec3 points[CUBE_NB_POINTS];
    glm::dvec3 centerPosition;
    // in radians
    glm::dvec3 rotation;
    glm::dvec3 dimension;
    
    static int segmentsIndexes[CUBE_NB_SEG_PER_CUBE*2];


public:
    bool isIntersectingWithCube2(Cube cube2);

    glm::dmat4 getCubeInvMatrix();

    void updateCubePoints();

    void displayCubeLines(std::string prefix);
    
    static std::vector<Cube> readCubes();
};

#endif /* Cube_hpp */
