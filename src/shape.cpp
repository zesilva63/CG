#include <cmath>
#include "shape.h"

using std::vector;

Shape::Shape(vector<Vertex*> vs, vector<Vertex*> ns, vector<Vertex*> te) {
    vertices = vs;
    normals = ns;
    texture = te;
}

Shape::Shape() { }

void get_vertex(int i, Vertex** vertex, Vertex** normal, Vertex** te) {
    *vertex = vertices.at(i);
    *normal = normals.at(i);
    *te = texture.at(i);

}

void push_vertex(Vertex* v) {
    vertices.push_back(v);
}

void push_normal(Vertex* n) {
    normals.push_back(n);
}

void push_texture(Vertex* t) {
    texture.push_back(t);
}

void push_shape(Shape* s) {
    vertices.insert(vertices.end(), s.vertices.begin(), s.vertices.end());
    normals.insert(normals.end(), s.normals.begin(), s.normals.end());
    texture.insert(texture.end(), s.texture.begin(), s.texture.end());
}

void reverse() {
    std::reverse(vertices.begin(), vertices.end());
    std::reverse(normals.begin(), normals.end());
    std::reverse(texture.begin(), texture.end());
}

int size() {
    return vertices.size();
}

Shape::~Shape(void) {}
