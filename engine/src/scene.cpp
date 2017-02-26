#include "scene.h"
#include <fstream>
#include <iostream>

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

std::vector<Vertex*> scene::get_vertices() {
    std::vector<Vertex*> copy = vertices;
    return copy;
}

void scene::parse(const char *filename) {
    XMLDocument doc;
    XMLNode *node;
    XMLElement *elem;

    doc.LoadFile(filename);

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
    std::ifstream infile(filename);

    while(std::getline(infile, line)) {
        Vertex *v = new Vertex(line);
        vertices.push_back(v);
    }
}
