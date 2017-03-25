#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include "operation.h"
#include "../../src/vertex.h"

class Model {
    public:
        void parse(const char* filename);
        void render();

    private:
        std::vector<Vertex*> vertices;
};

class Group {
    public:
        void render();
        void add_operation(Operation *op);
        void add_model(Model *m);
        void add_child(Group *grp);
<<<<<<< HEAD
        bool has_models();
        bool has_operation(const char* type);
=======
>>>>>>> 97eb00b... Implements ship, colors and camera

    private:
        std::vector<Operation*> ops;
        std::vector<Model*> models;
        std::vector<Group*> children;
};

#endif
