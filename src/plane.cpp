#include "plane.h"

using std::vector;

vector<Vertex*> plane(float size) {
    vector<Vertex*> r;
    float v = size/2;

    r.push_back(new Vertex(v, 0, v));
    r.push_back(new Vertex(v, 0, -v));
    r.push_back(new Vertex(-v, 0, v));

    r.push_back(new Vertex(-v, 0, v));
    r.push_back(new Vertex(v, 0, -v));
    r.push_back(new Vertex(-v, 0, -v));

    return r;
}
