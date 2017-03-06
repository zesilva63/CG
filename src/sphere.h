#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include "vertex.h"

std::vector<Vertex*> sphere(double raio, int verticalLayers, int horizontalLayers);

#endif
