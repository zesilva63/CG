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

GLuint buffers[1];

void Model::setColor(XMLElement* model) {
    int cred = 255, cgreen = 255, cblue = 255;

    model->QueryIntAttribute("R", &cred);
    model->QueryIntAttribute("G", &cgreen);
    model->QueryIntAttribute("B", &cblue);

    red = (double) cred / 255;
    green = (double) cgreen / 255;
    blue = (double) cblue / 255;
}

void Model::parse(XMLElement* model) {
    string line;
    const char* filename = model->Attribute("file");
    ifstream ifile(filename);
    n=0;
    int indice =0;

    setColor(model);

    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + filename);

    while(getline(ifile,line)) n++;
    
    ifile.clear();
    ifile.seekg(0, std::ios::beg);

    vertexData = (float*) malloc((n+1)*3*sizeof(float));
    glGenBuffers(1, buffers);

    while(getline(ifile, line)) {
        try {
            Vertex *v = new Vertex(line);
            vertexData[indice++]=v->getX();
            vertexData[indice++]=v->getY();
            vertexData[indice++]=v->getZ();   
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
}

void Model::render() {
    glBufferData(GL_ARRAY_BUFFER,n*3*sizeof(float),vertexData,GL_STATIC_DRAW);
    glColor3f(red, green, blue);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLE_STRIP,0,n);
    glColor3f(1, 1, 1);
}

void Group::render() {
    glPushMatrix();
    for(Operation *op: ops)
        op->apply();

    for(Translate *tran: trans)
        tran->apply();

    for(Rotate *rot: rots)
        rot->apply();

    for(Group *chld : children)
        chld->render();
    
    for(Model *m: models)
        m->render();

    glPopMatrix();
}

void Group::add_operation(Operation *op) {
    ops.push_back(op);
}

void Group::add_rotate(Rotate* rot) {
    rots.push_back(rot);
}

void Group::add_translate(Translate* tran) {
    trans.push_back(tran);
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
