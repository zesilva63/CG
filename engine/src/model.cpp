#include <GL/glut.h>
#include <fstream>
#include <exception>
#include "model.h"

using std::string;
using std::ifstream;
using std::getline;
using std::exception;

void Model::parse(const char* filename) {
    string line;
    ifstream ifile(filename);

    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + filename);

    while(getline(ifile, line)) {
        try {
            Vertex *v = new Vertex(line);
            vertices.push_back(v);
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }
}

void Model::render() {
    glBegin(GL_TRIANGLES);
    for (Vertex *v: vertices)
        glVertex3f(v->getX(), v->getY(), v->getZ());
    glEnd();
}

void Group::render() {
    glPushMatrix();

    for(Operation *op: ops)
        op->apply();

    for(Model *m: models)
        m->render();

    for(Group *chld : children)
        chld->render();

    glPopMatrix();
}

void Group::add_operation(Operation *op) {
    ops.push_back(op);
}

void Group::add_model(Model *m) {
    models.push_back(m);
}

void Group::add_child(Group *grp) {
    children.push_back(grp);
}

bool Group::has_models() {
    return !models.empty();
}

bool Group::has_operation(const char* type) {
    for(Operation *op: ops)
        if (!strcmp(op->type(), type))
            return true;

    return false;
}
