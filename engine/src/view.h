#ifndef __VIEW__
#define __VIEW__

#include <vector>
#include <tinyxml2.h>
#include "model.h"

class View {
    public:
        void parse(std::string filename);
        void render();

    private:
        std::vector<Group*> groups;
        std::string dirname;
        Group* parse_group(tinyxml2::XMLNode *nd);
        void parse_model(Group* grp, tinyxml2::XMLNode *nd);
        void parse_scale(Group* grp, tinyxml2::XMLNode *nd);
        void parse_models(Group* grp, tinyxml2::XMLNode *nd);
        void parse_translate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_rotate(Group* grp, tinyxml2::XMLNode *nd);
        void parse_color(Group* grp, tinyxml2::XMLNode *nd);
};

#endif
