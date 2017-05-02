#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <exception>
#include <iostream>
#include "model.h"

using std::string;
using std::ifstream;
using std::getline;
using std::exception;
using tinyxml2::XMLElement;

void Model::setColor(XMLElement* model) {
    int cred = 255, cgreen = 255, cblue = 255;

    model->QueryIntAttribute("R", &cred);
    model->QueryIntAttribute("G", &cgreen);
    model->QueryIntAttribute("B", &cblue);

    red = (double) cred / 255;
    green = (double) cgreen / 255;
    blue = (double) cblue / 255;
}

void Model::parse(string directory, XMLElement* model) {
    string line, filename = string( model->Attribute("file") );
    int size;

    setColor(model);

    ifstream ifile((directory + filename).c_str());
    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + filename);

    while(getline(ifile, line)) {
        try {
            Vertex *v = new Vertex(line);
            vertices.push_back(v->getX());
            vertices.push_back(v->getY());
            vertices.push_back(v->getZ());
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }

    glGenBuffers(1, &buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);

    size = vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
}

void Model::render() {
    int size = vertices.size() * sizeof(float);

    glColor3f(red, green, blue);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, size / 3);

    glColor3f(1, 1, 1);
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
    if (has_models())
        throw std::domain_error("Geometric transformations should be specified before models");

    if (has_operation(op->type()))
        throw std::domain_error("There must be only a geometric transformation of the same type inside a group");

    ops.push_back(op);
}

void Group::add_model(Model *m) {
    if (has_models())
        throw std::domain_error("Geometric transformations should be specified before models");

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
