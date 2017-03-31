#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <tinyxml2.h>
#include "operation.h"
#include "model.h"
#include "../../src/vertex.h"

class Scene {
    public:
        void parse(std::string filename);
        void render();

    private:
        std::vector<Group*> groups;
};

#endif
