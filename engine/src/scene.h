#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <tinyxml2.h>
#include "operation.h"
#include "model.h"
#include "light.h"
#include "../../src/vertex.h"

class Scene {
    public:
        void parse(std::string filename);
        void render();
        void define_lights();

    private:
        std::vector<Group*> groups;
        std::vector<Light*> lights;
        Group* parse_group(tinyxml2::XMLNode *nd);
        void parse_lights(tinyxml2::XMLNode *nd);
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
