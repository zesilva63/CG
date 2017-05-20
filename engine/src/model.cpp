#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <exception>
#include "model.h"
#include <IL/il.h>

using std::string;
using std::ifstream;
using std::getline;
using std::exception;
using tinyxml2::XMLElement;
using tinyxml2::XMLError;

using std::vector;

Model::Model() {
    vertices = 0;
    normals = 0;
    texture = 0;
    tex_points = 0;
    color[3] = 1.0f;
}

bool Model::parse_diffuse(XMLElement* model) {
    XMLError r1 = model->QueryFloatAttribute("diffR", &color[0]);
    XMLError r2 = model->QueryFloatAttribute("diffG", &color[1]);
    XMLError r3 = model->QueryFloatAttribute("diffB", &color[2]);

    light_type = GL_DIFFUSE;
    return !r1 && !r2 && !r3;
}

bool Model::parse_specular(XMLElement* model) {
    XMLError r1 = model->QueryFloatAttribute("specR", &color[0]);
    XMLError r2 = model->QueryFloatAttribute("specG", &color[1]);
    XMLError r3 = model->QueryFloatAttribute("specB", &color[2]);

    light_type = GL_SPECULAR;
    return !r1 && !r2 && !r3;
}

bool Model::parse_emission(XMLElement* model) {
    XMLError r1 = model->QueryFloatAttribute("emiR", &color[0]);
    XMLError r2 = model->QueryFloatAttribute("emiG", &color[1]);
    XMLError r3 = model->QueryFloatAttribute("emiB", &color[2]);

    light_type = GL_EMISSION;
    return !r1 && !r2 && !r3;
}

bool Model::parse_ambient(XMLElement* model) {
    XMLError r1 = model->QueryFloatAttribute("ambR", &color[0]);
    XMLError r2 = model->QueryFloatAttribute("ambG", &color[1]);
    XMLError r3 = model->QueryFloatAttribute("ambB", &color[2]);

    light_type = GL_AMBIENT;
    return !r1 && !r2 && !r3;
}

bool Model::parse_light(XMLElement* model) {
    return parse_diffuse(model)  ||
           parse_specular(model) ||
           parse_emission(model) ||
           parse_ambient(model);
}

void Model::parse(string directory, XMLElement* model) {
    string line, filename = string(model->Attribute("file"));
    vector<float> *vec;
    Shape s;

    parse_texture(directory, model);
    parse_light(model);
    s.load_file(directory + filename);
    glGenBuffers(3, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    vec = s.get_vertices();
    vertices = vec->size();
    glBufferData(GL_ARRAY_BUFFER, vertices*sizeof(float), vec->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    vec = s.get_normals();
    normals = vec->size();
    glBufferData(GL_ARRAY_BUFFER, normals*sizeof(float), vec->data(), GL_STATIC_DRAW);

    glBindTexture(GL_ARRAY_BUFFER, buffers[2]);
    vec = s.get_texture();
    tex_points = vec->size();
    glBufferData(GL_ARRAY_BUFFER, tex_points*sizeof(float), vec->data(), GL_STATIC_DRAW);
}

void Model::parse_texture(string directory, XMLElement* model) {
    const char *filename = model->Attribute("texture");

    if (filename == NULL)
        return;

    load_texture((directory + string(filename)).c_str());
}

void Model::load_texture(const char* tex_file) {
    unsigned int t,tw,th;
    unsigned char *texData;
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring) tex_file);

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
}

void Model::render() {
    glMaterialfv(GL_FRONT, light_type, color);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices / 3);
    glBindTexture(GL_TEXTURE_2D, 0);
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
