#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <tinyxml2.h>
#include "operation.h"
#include "translate.h"
#include "rotate.h"
#include "../../src/vertex.h"

class Model {
    public:
        void parse(tinyxml2::XMLElement *model);
        void render();

    private:
        float *vertexData;
        std::vector<Vertex*> vertices;
        double red, green, blue;
        void setColor(tinyxml2::XMLElement *model);
};

class Group {
    public:
        void render();
        void add_operation(Operation *op);
        void add_rotate(Rotate *rot);
        void add_translate(Translate *trans);
        void add_model(Model *m);
        void add_child(Group *grp);
        bool has_models();
        bool has_operation(const char* type);

    private:
        std::vector<Operation*> ops;
        std::vector<Rotate*> rots;
        std::vector<Translate*> trans;
        std::vector<Model*> models;
        std::vector<Group*> children;
        int normal;
};

#endif
