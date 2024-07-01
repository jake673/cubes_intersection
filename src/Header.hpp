//
//  Header.hpp
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <set>
//#include <format>
#include <chrono>
#include <map>

#define GL_SILENCE_DEPRECATION
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#pragma clang diagnostic pop

#undef GL_SILENCE_DEPRECATION

// in meters
#define CST_EPSILON 0.0001

#endif /* Header_h */
