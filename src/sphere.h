#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>

#include <math.h>
#include <string>

#include <vector>

#include "vertex.h"

std::vector<Vertex*> sphere(double raio, int slices, int stacks);

#endif
