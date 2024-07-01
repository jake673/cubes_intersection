//
//  Geometry.hpp
//

#ifndef Geometry_hpp
#define Geometry_hpp

class Geometry {
public:
    
    static bool isPointInsideDimension(glm::dvec3 pt, glm::dvec3 dim);
    
    static bool isSegmentInsideDimension(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim);
    static bool isSegmentInsideDimensionZ(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim);
    static bool isSegmentInsideDimensionX(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim);
    static bool isSegmentInsideDimensionY(glm::dvec3 pt1, glm::dvec3 pt2, glm::dvec3 dim);

    static void displayLines(std::string prefix, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4);
    
};


#endif /* Geometry_hpp */
