#ifndef __PATCH_H__
#define __PATCH_H__

#include <vector>

#include "../../src/vertex.h"
#include "../../src/shape.h"



/*
Generates an list of surfaces from a given patch
@param file, name of the file where the patch is
@param tesselate, number of precision to make the bezier surface
@returns a vector with all the vertices of generated surfaces
*/
Shape *patch(char * file,int n);

#endif
