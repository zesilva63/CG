#ifndef __CUBE_H__
#define __CUBE_H__

#include <vector>
#include "../../src/vertex.h"

/**
 * Generates a cube with x length, z width and y height
 * divided in n parts centered in the origin.
 * @param x lenght of cube
 * @param y height of cube
 * @param z width of cube
 * @param n number of divisions
 * @returns a vector with all the vertices of generated cube
 */
std::vector<Vertex*> cube(float x, float y, float z, int n);

#endif
