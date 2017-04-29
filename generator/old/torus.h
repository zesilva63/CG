#ifndef __TORUS_H__
#define __TORUS_H__

#include <vector>

#include "../../src/vertex.h"

/*
Generates a cone with a given base radius, height, slices and stacks by the user 
@param radius , radius of the base of the cone
@param height, height of cone
@param slices, number of sides of the cone
@param stacks, number of divisions vertically
@returns a vector with all the vertices of generated cone
*/
std::vector<Vertex*> torus(float inner_radius, float outter_radius, int slices, int stacks);

#endif
