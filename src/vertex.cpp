#include "vertex.h"

Vertex::Vertex(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;
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

Vertex::~Vertex(void) {}
