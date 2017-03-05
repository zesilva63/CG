#include "scene.h"
#include <fstream>
#include <iostream>
#include <exception>

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

std::vector<Vertex*> scene::get_vertices() {
    std::vector<Vertex*> copy = vertices;
    return copy;
}

void scene::parse(std::string filename) {
    XMLDocument doc;
    XMLNode *node;
    XMLElement *elem;

    doc.LoadFile(filename.c_str());

    if ((node = doc.FirstChild()))
        node = node->FirstChild();

    for(; node; node = node->NextSibling()) {
        elem = node->ToElement();

        if (!strcmp(node->Value(), "model"))
            parse_model(elem);
    }
}

void scene::parse_model(XMLElement *model) {
    const char* filename = model->Attribute("file");
    std::string line;
    std::ifstream ifile(filename);

    if (ifile.fail())
        throw std::ios_base::failure(std::string("Couldn't find file: ") + filename);

    while(std::getline(ifile, line)) {
        try {
            Vertex *v = new Vertex(line);
            vertices.push_back(v);
        } catch (std::exception& e) {
            throw std::invalid_argument(std::string("Couldn't parse file ") + filename + ": " + e.what());
        }
    }
}
