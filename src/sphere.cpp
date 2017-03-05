#include "sphere.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using std::vector;

#define PI  3.14159265358979323846

std::vector<Vertex*> sphere(double radius, int verticalLayers, int horizontalLayers) {

    std::vector<Vertex*> points;
    int i, j;
    float teta = 0, fi = 0;
    float jumpH = PI / horizontalLayers;
    float jumpV = (2 * PI) / verticalLayers;
    float x1, y1, z1, x2, y2, z2, x3, y3, z3;

    for (i = 0; i < horizontalLayers; i++) {
        teta = 0;

        for (j = 0; j < verticalLayers; j++) {

            x1 = radius*sin(fi)*sin(teta);
            y1 = radius*cos(fi);
            z1 = radius*cos(teta)*sin(fi);

            x2 = radius*sin(fi + jumpH)*sin(teta + jumpV);
            y2 = radius*cos(fi + jumpH);
            z2 = radius*cos(teta + jumpV)*sin(fi + jumpH);

            x3 = radius*sin(fi + jumpH)*sin(teta);
            y3 = radius*cos(fi + jumpH);
            z3 = radius*cos(teta)*sin(fi + jumpH);

            points.push_back(new Vertex(x1, y1, z1));
            points.push_back(new Vertex(x2, y2, z2));
            points.push_back(new Vertex(x3, y3, z3));

            teta += jumpV;
        }
        fi += jumpH;
	}

    return points;
}
