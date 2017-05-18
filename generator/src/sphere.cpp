#include "sphere.h"

#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/vertex.h"

using std::vector;

#define PI 3.14159265358979323846

void xyz_to_uv(float x, float y, float z, float* u, float* v);

Shape* sphere(double radius, int verticalLayers, int horizontalLayers) {

    Shape* points = new Shape();
    Vertex* normal;
    int i, j;
    float theta = 0, phi = 0;
    float jumpH = PI / horizontalLayers;
    float jumpV = (2 * PI) / verticalLayers;
    float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, u, v;

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

            x4 = radius*sin(phi)*sin(theta + jumpV);
            y4 = radius*cos(phi);
            z4 = radius*sin(phi)*cos(theta + jumpV);

            points->push_vertex(new Vertex(x1, y1, z1));
            normal = Vertex::normalize(new Vertex(x1, y1, z1));
            points->push_normal(normal);
            xyz_to_uv(x1, y1, z1, &u, &v);
            points->push_texture(new Vertex(u, v));

            points->push_vertex(new Vertex(x2, y2, z2));
            normal = Vertex::normalize(new Vertex(x2, y2, z2));
            points->push_normal(normal);
            xyz_to_uv(x2, y2, z2, &u, &v);
            points->push_texture(new Vertex(u, v));

            points->push_vertex(new Vertex(x3, y3, z3));
            normal = Vertex::normalize(new Vertex(x3, y3, z3));
            points->push_normal(normal);
            xyz_to_uv(x3, y3, z3, &u, &v);
            points->push_texture(new Vertex(u, v));

            points->push_vertex(new Vertex(x1, y1, z1));
            normal = Vertex::normalize(new Vertex(x1, y1, z1));
            points->push_normal(normal);
            xyz_to_uv(x1, y1, z1, &u, &v);
            points->push_texture(new Vertex(u, v));

            points->push_vertex(new Vertex(x4, y4, z4));
            normal = Vertex::normalize(new Vertex(x4, y4, z4));
            points->push_normal(normal);
            xyz_to_uv(x4, y4, z4, &u, &v);
            points->push_texture(new Vertex(u, v));

            points->push_vertex(new Vertex(x2, y2, z2));
            normal = Vertex::normalize(new Vertex(x2, y2, z2));
            points->push_normal(normal);
            xyz_to_uv(x2, y2, z2, &u, &v);
            points->push_texture(new Vertex(u, v));


            theta += jumpV;
        }
        phi += jumpH;
    }

    return points;
}

void xyz_to_uv(float x, float y, float z, float* u, float* v) {
    Vertex* normal = Vertex::normalize(new Vertex(x, y, z));

    *u = 0.5 + atan2(normal->getZ(), normal->getX()) / (2* PI);
    *v = 0.5 - asin(normal->getY()) / PI;

    /**u = asin(normal->getX() * x) / PI + 0.5;
    *v = asin(normal->getY() * y) / PI + 0.5; */
}
