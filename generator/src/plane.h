#ifndef __PLANE_H__
#define __PLANE_H__

#include <vector>
#include <iostream>
#include <fstream>

#include "../../src/shape.h"


/**
 * Generates a square in the XZ plane, centered in the origin.
 * @param size size of square
 * @returns a Shape with all the information of the generated plane
 */
Shape* plane(float size);

#endif
