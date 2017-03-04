#ifndef __PLANE_H__
#define __PLANE_H__

#include <vector>
#include <iostream>
#include <fstream>

#include "../../vertex.h"


/**
 * Generates a square in the XZ plane, centered in the origin.
 * @param size size of square
 * @returns a vector with all the vertices generated for the plane
 */
std::vector<Vertex*> plane(float size);

#endif
