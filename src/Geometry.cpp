//
//  Geometry.cpp
//

#include "Header.hpp"
#include "Geometry.hpp"


bool Geometry::isPointInsideDimension(glm::dvec3 pt, glm::dvec3 dim) {
    if ( ( pt.x < (-dim.x/2) ) || ( pt.x > (dim.x/2) ) ) {return false;}
    if ( ( pt.y < (-dim.y/2) ) || ( pt.y > (dim.y/2) ) ) {return false;}
    if ( ( pt.z < (-dim.z/2) ) || ( pt.z > (dim.z/2) ) ) {return false;}
    return true;
}


bool Geometry::isSegmentInsideDimensionZ(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim) {
    // Line : (pt2-pt1) * t1 + pt1 : Plane z = dim/2
    // (pt2.z - pt1.z) * t1 + pt1.z = (dim/2)
    double z1 = pt2.z - pt1.z;
    if (abs(z1) < CST_EPSILON ) {
        if ( ( pt1.z > (dim.z/2) ) || ( pt1.z < (-dim.z/2) ) ) {
            // outside the dimension
            return false;
        } else {
            // coplanar or inside the dim :
            // check if Pt1 - Pt2 crosses the dimension
            // will be checked in the other axis
            return false;
        }
    } else {
        // plane z = dim.z/2
        double t1 = (dim.z/2 - pt1.z) / z1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
        // plane z = -dim.z/2
        t1 = (-dim.z/2 - pt1.z) / z1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::isSegmentInsideDimensionX(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim) {
    double x1 = pt2.x - pt1.x;
    if (abs(x1) < CST_EPSILON ) {
        if ( ( pt1.x > (dim.x/2) ) || ( pt1.x < (-dim.x/2) ) ) {
            // outside the dimension
            return false;
        } else {
            // coplanar or inside the dim :
            // check if Pt1 - Pt2 crosses the dimension
            // will be checked in the other axis
            return false;
        }
    } else {
        // plane x = dim.x/2
        double t1 = (dim.x/2 - pt1.x) / x1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
        // plane x = -dim.x/2
        t1 = (-dim.x/2 - pt1.x) / x1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::isSegmentInsideDimensionY(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim) {
    double y1 = pt2.y - pt1.y;
    if (abs(y1) < CST_EPSILON ) {
        if ( ( pt1.y > (dim.y/2) ) || ( pt1.y < (-dim.y/2) ) ) {
            // outside the dimension
            return false;
        } else {
            // co planar == or inside the dim :
            // check if Pt1 - Pt2 crosses the dimension
            // will be checked in the other axis
            return false;
        }
    } else {
        // plane y = dim.y/2
        double t1 = (dim.y/2 - pt1.y) / y1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
        // plane y = -dim.y/2
        t1 = (-dim.y/2 - pt1.y) / y1;
        if ( (t1 >= 0) && (t1 <= 1) ) {
            glm::dvec3 ptInter = (pt2-pt1) * t1 + pt1;
            if (isPointInsideDimension(ptInter, dim)) {
                return true;
            }
        }
    }
    return false;
}

bool Geometry::isSegmentInsideDimension(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim) {
    if (isSegmentInsideDimensionZ(pt1, pt2, dim)) {
        return true;
    }
    if (isSegmentInsideDimensionX(pt1, pt2, dim)) {
        return true;
    }
    if (isSegmentInsideDimensionY(pt1, pt2, dim)) {
        return true;
    }
    return false;
}

/*
 for testing purpose : script to add / display lines in Blender
 see blender script : Save-Cubes-02.py
 */
void Geometry::displayLines(std::string prefix, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4) {
    //double off1 = 0.05;
    //std::cout << "displayLines off1 " << off1 << std::endl;
    std::cout << "updateLine( \""<< prefix <<"pt1-2\", ( " << p1.x << "," << p1.y << "," << p1.z << " ),(" << p2.x << "," << p2.y << "," << p2.z << " ) ); " << std::endl;
    std::cout << "updateLine( \""<< prefix <<"pt2-3\", ( " << p2.x << "," << p2.y << "," << p2.z << " ),(" << p3.x << "," << p3.y << "," << p3.z << " ) ); " << std::endl;
    std::cout << "updateLine( \""<< prefix <<"pt3-4\", ( " << p3.x << "," << p3.y << "," << p3.z << " ),(" << p4.x << "," << p4.y << "," << p4.z << " ) ); " << std::endl;
}
