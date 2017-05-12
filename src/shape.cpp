#include <cmath>
#include <algorithm>
#include "shape.h"

using std::vector;
using std::ifstream;
using std::string;

Shape::Shape(vector<Vertex*> vs, vector<Vertex*> ns, vector<Vertex*> te) {
    vertices = vs;
    normals = ns;
    texture = te;
}

Shape::Shape() { }

Shape::Shape(string file_path) {
    string line;
    char t;

    ifstream ifile (file_path, std::ifstream::in);

    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + file_path);

    while(getline(ifile, line)) {
        t = line[0];
        line.erase(0,2);
        switch(t) {
            case 'V': vertices.push_back(new Vertex(line));
                      break;
            case 'N': normals.push_back(new Vertex(line));
                      break;
            case 'T': texture.push_back(new Vertex(line));
                      break;
        }
    }

    ifile.close();
}

void Shape::get_vertex(int i, Vertex** vertex, Vertex** normal, Vertex** te) {
    *vertex = vertices.at(i);
    *normal = normals.at(i);
    *te = texture.at(i);

}

void Shape::push_vertex(Vertex* v) {
    vertices.push_back(v);
}

void Shape::push_normal(Vertex* n) {
    normals.push_back(n);
}

void Shape::push_texture(Vertex* t) {
    texture.push_back(t);
}

void Shape::push_shape(Shape* s) {
    vertices.insert(vertices.end(), s->vertices.begin(), s->vertices.end());
    normals.insert(normals.end(), s->normals.begin(), s->normals.end());
    texture.insert(texture.end(), s->texture.begin(), s->texture.end());
}

void Shape::reverse() {
    std::reverse(vertices.begin(), vertices.end());
    std::reverse(normals.begin(), normals.end());
    std::reverse(texture.begin(), texture.end());
}

int Shape::size() {
    return vertices.size();
}

Shape::~Shape(void) {}
