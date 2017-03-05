#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include "vertex.h"

std::vector<Vertex*> sphere(double radious, int slicesV, int stacksH, std::string file_name);

#endif
