#ifndef __CONE_H__
#define __CONE_H__

#include <vector>

#include "../../src/vertex.h"
#include "../../src/shape.h"

/*
Generates a cone with a given base radius, height, slices and stacks by the user 
@param radius , radius of the base of the cone
@param height, height of cone
@param slices, number of sides of the cone
@param stacks, number of divisions vertically
@returns a vector with all the vertices of generated cone
*/
Shape* cone(float radius, float height, int slices, int stacks);

#endif
