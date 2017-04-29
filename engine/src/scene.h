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
        Group* parse_group(tinyxml2::XMLNode *nd);
        void parse_model(Group* grp, tinyxml2::XMLNode *nd);
        void parse_scale(Group* grp, tinyxml2::XMLNode *nd);
        void parse_models(Group* grp, tinyxml2::XMLNode *nd);
        void parse_ImediateRotate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_ImediateTranslate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_translate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_rotate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_color(Group* grp, tinyxml2::XMLNode *nd);
};

#endif
