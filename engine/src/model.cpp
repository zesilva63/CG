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

using std::vector;

Model::Model() {
    vertices = 0;
    normals = 0;
    texture = 0;
    tex_points = 0;
    shininess = 0;
}

void Model::parse_material(XMLElement* model) {
    model->QueryFloatAttribute("diffR", &diffuse[0]);
    model->QueryFloatAttribute("diffG", &diffuse[1]);
    model->QueryFloatAttribute("diffB", &diffuse[2]);

    model->QueryFloatAttribute("specR", &specular[0]);
    model->QueryFloatAttribute("specG", &specular[1]);
    model->QueryFloatAttribute("specB", &specular[2]);

    model->QueryFloatAttribute("emiR", &emission[0]);
    model->QueryFloatAttribute("emiG", &emission[1]);
    model->QueryFloatAttribute("emiB", &emission[2]);

    model->QueryFloatAttribute("ambR", &ambient[0]);
    model->QueryFloatAttribute("ambG", &ambient[1]);
    model->QueryFloatAttribute("ambB", &ambient[2]);

    model->QueryFloatAttribute("shine", &shininess);
}

void Model::render_material() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

}

void Model::parse(string directory, XMLElement* model) {
    string line, filename = string(model->Attribute("file"));
    vector<float> *vec;
    Shape s;

    parse_texture(directory, model);
    parse_material(model);
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


void Model::load_texture(std::string s) {

    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1,&texID);
    
    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,      GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER,      GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->texture = texID;

}



void Model::render() {
    render_material();
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

    glFlush();
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
