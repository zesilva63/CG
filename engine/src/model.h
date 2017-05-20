#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <tinyxml2.h>
#include "operation.h"
#include "translate.h"
#include "rotate.h"
#include "../../src/vertex.h"
#include "../../src/shape.h"

class Model {
    public:
        Model();
        void parse(std::string directory, tinyxml2::XMLElement *model);
        void render();

    private:
        int vertices, normals, tex_points;
        GLuint texture, buffers[3];
        float ambient[4] = {0.2, 0.2, 0.2, 1};
        float diffuse[4] = {0.8, 0.8, 0.8, 1};
        float specular[4] = {0, 0, 0, 1};
        float emission[4] = {0, 0, 0, 1};
        float shininess;
        GLenum light_type;
        void parse_material(tinyxml2::XMLElement *model);
        void render_material();
        void parse_texture(std::string directory, tinyxml2::XMLElement* model);
        void load_texture(const char* tex_file);
};

class Group {
    public:
        void render();
        void add_operation(Operation *op);
        void add_model(Model *m);
        void add_child(Group *grp);
        bool has_models();
        bool has_operation(const char* type);

    private:
        std::vector<Operation*> ops;
        std::vector<Model*> models;
        std::vector<Group*> children;
        int normal;
};

#endif
