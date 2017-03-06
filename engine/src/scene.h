#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <tinyxml2.h>
#include "../../src/vertex.h"

class scene {
    public:
        std::vector<Vertex*> get_vertices();
        void parse(std::string filename);

    private:
        std::vector<Vertex*> vertices;
        void parse_model(tinyxml2::XMLElement *model);
};

#endif
