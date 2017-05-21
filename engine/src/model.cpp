#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <exception>
#include <iostream>
#include <IL/il.h>
#include "model.h"

using std::string;
using std::ifstream;
using std::getline;
using std::exception;
using tinyxml2::XMLElement;


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
        textureData[textureI++]=v->getZ();
    }
}


void Model::loadTexture(std::string s) {

    unsigned int t,tw,th;
    
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    
    glGenTextures(1,&texID);
    
    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,      GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER,      GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::parse_texture(string directory, XMLElement* model) {
    const char *filename = model->Attribute("texture");

    if (filename == NULL)
        return;

    loadTexture((directory + string(filename)).c_str());
}


void Model::parse(XMLElement* model) {
    string line;
    const char* filename = model->Attribute("file");
    ifstream ifile( string("example/3d/") + filename);
    n=0;

    parse_texture("example/tex/", model);
    parse_material(model);

    if (ifile.fail())
        throw std::ios_base::failure(string("Couldn't find file: ") + filename);

    while(getline(ifile,line)) n++;


    
    n= n/3;

    ifile.clear();
    ifile.seekg(0, std::ios::beg);

    vertexData = (float*) malloc((n+1)*3*sizeof(float));
    glGenBuffers(1, vertex);

    normalData = (float*) malloc((n+1)*3*sizeof(float));
    glGenBuffers(1, normal);


    textureData = (float*) malloc((n+1)*3*sizeof(float));
    glGenBuffers(1, texture);


    while(getline(ifile, line)) {
        try {
            parse_line(line);  
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertex[0]);
    glBufferData(GL_ARRAY_BUFFER,vertexI*sizeof(float),vertexData,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, normal[0]);
    glBufferData(GL_ARRAY_BUFFER,normalI*sizeof(float),normalData,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texture[0]);
    glBufferData(GL_ARRAY_BUFFER,textureI*sizeof(float),textureData,GL_STATIC_DRAW);
    
}


void Model::render_material() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}

void Model::render() {
    glBindTexture(GL_TEXTURE_2D, texID);
    render_material();
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex[0]);
    glVertexPointer(3, GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,normal[0]);
    glNormalPointer(GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,texture[0]);
    glTexCoordPointer(2,GL_FLOAT,0,0);
    
    glDrawArrays(GL_TRIANGLE_STRIP,0,n);

    glBindTexture(GL_TEXTURE_2D, 0);
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

    glFlush();
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
