//
//  main.cpp
//

#include "Header.hpp"
#include "Cube.hpp"
#include "Geometry.hpp"

void test1() {
    //
    std::vector<Cube> cubes = Cube::readCubes();
    if (cubes.size() < 2) {return;}
    //
    bool intersect = cubes[0].isIntersectingWithCube2( cubes[1] );
    std::cout << "intersect: " << intersect << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "3D Cubes Intersection" << std::endl;
    
    test1();

}

