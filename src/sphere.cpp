#include "sphere.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using std::vector;

#define PI  3.14159265358979323846

std::vector<Vertex*> sphere(double radius, int verticalLayers, int horizontalLayers) {

    std::vector<Vertex*> points;
    int i, j;
    float theta = 0, phi = 0;
    float jumpH = PI / horizontalLayers;
    float jumpV = (2 * PI) / verticalLayers;
    float x1, y1, z1, x2, y2, z2, x3, y3, z3;

    for (i = 0; i < horizontalLayers; i++) {
        theta = 0;

        for (j = 0; j < verticalLayers; j++) {

            x1 = radius*sin(phi)*sin(theta);
            y1 = radius*cos(phi);
            z1 = radius*cos(theta)*sin(phi);

            x2 = radius*sin(phi + jumpH)*sin(theta + jumpV);
            y2 = radius*cos(phi + jumpH);
            z2 = radius*cos(theta + jumpV)*sin(phi + jumpH);

            x3 = radius*sin(phi + jumpH)*sin(theta);
            y3 = radius*cos(phi + jumpH);
            z3 = radius*cos(theta)*sin(phi + jumpH);

            points.push_back(new Vertex(x1, y1, z1));
            points.push_back(new Vertex(x2, y2, z2));
            points.push_back(new Vertex(x3, y3, z3));

            theta += jumpV;
        }
        phi += jumpH;
    }

    return points;
}
