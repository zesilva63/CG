#include "plane.h"
#include "../../src/vertex.h"

using std::vector;

Shape* plane(float size) {
    Shape* r = new Shape();

    float v = size/2;

    r->push_vertex(new Vertex(v, 0, v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(1, 1));

    r->push_vertex(new Vertex(v, 0, -v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(1, 0));

    r->push_vertex(new Vertex(-v, 0, v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(0, 1));



    r->push_vertex(new Vertex(-v, 0, v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(0, 1));

    r->push_vertex(new Vertex(v, 0, -v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(1, 0));

    r->push_vertex(new Vertex(-v, 0, -v));
    r->push_normal(new Vertex(0, 1, 0));
    r->push_texture(new Vertex(0, 0));

    return r;
}
