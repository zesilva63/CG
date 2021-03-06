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
void Model::parse(XMLElement* model) {
    string line;
    const char* filename = model->Attribute("file");
    ifstream ifile( string("example/") + filename);
    int n=0;

    parse_texture("example/", model);
    parse_material(model);

    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + filename);

    while(getline(ifile,line)) n++;



    n= n/3;

    ifile.clear();
    ifile.seekg(0, std::ios::beg);

    glGenBuffers(3, buffers);
    vertexData = (float*) malloc((n+1)*3*sizeof(float));
    normalData = (float*) malloc((n+1)*3*sizeof(float));
    textureData = (float*) malloc((n+1)*3*sizeof(float));


    while(getline(ifile, line)) {
        try {
            parse_line(line);
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,vertexI*sizeof(float),vertexData,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,normalI*sizeof(float),normalData,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER,textureI*sizeof(float),textureData,GL_STATIC_DRAW);

}

void Model::parse_line(string line){
    if(line[0]=='V'){
        line.erase(0,2);
        Vertex *v = new Vertex(line);
        vertexData[vertexI++]=v->getX();
        vertexData[vertexI++]=v->getY();
        vertexData[vertexI++]=v->getZ();
    }
    if(line[0]=='N'){
        line.erase(0,2);
        Vertex *v = new Vertex(line);
        normalData[normalI++]=v->getX();
        normalData[normalI++]=v->getY();
        normalData[normalI++]=v->getZ();
    }
    if(line[0]=='T'){
        line.erase(0,2);
        Vertex *v = new Vertex(line);
        textureData[textureI++]=v->getX();
        textureData[textureI++]=v->getY();
    }
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
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
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

    glDrawArrays(GL_TRIANGLES, 0, vertexI / 3);
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
