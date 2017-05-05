#include <cmath>
#include "vertex.h"

Vertex::Vertex(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;
}

Vertex::Vertex(float u, float v) {
    x = u;
    y = v;
    z = 0;
}

Vertex::Vertex(std::string str) {
    size_t sz;

    try {
        x = std::stof (str, &sz);
        str.erase(0, sz+1);
        y = std::stof (str, &sz);
        str.erase(0, sz+1);
        z = std::stof (str, &sz);
    } catch ( ... ) {
        throw std::invalid_argument ("The string must have 3 float numbers separated by a space");
    }
}

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

float Vertex::getZ() {
    return z;
}

// Subtraction of two points
Vertex* Vertex::sub(Vertex* p1, Vertex* p2) {
    float nx, ny, nz;

    nx = p1->x - p2->x;
    ny = p1->y - p2->y;
    nz = p1->z - p2->z;

    return new Vertex(nx, ny, nz);
}

// Cross product of two vectors
Vertex* Vertex::cross_product(Vertex* v1, Vertex* v2) {
    float nx, ny, nz;

    nx = v1->y * v2->z - v1->z * v2->y;
    ny = v1->z * v2->x - v1->x * v2->z;
    nz = v1->x * v2->y - v1->y * v2->x;

    return new Vertex(nx, ny, nz);
}

Vertex* Vertex::normalize(Vertex* v) {
    float l, nx, ny, nz;

    l = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    nx = v->x / l;
    ny = v->y / l;
    nz = v->z / l;

    return new Vertex(nx, ny, nz);
}

Vertex::~Vertex(void) {}
