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
        GLuint texture, buffers[3];
        float color[4];
        GLenum light_type;
        int vertices, normals, tex_points;
        bool parse_light(tinyxml2::XMLElement *model);
        bool parse_color(tinyxml2::XMLElement* model);
        bool parse_diffuse(tinyxml2::XMLElement* model);
        bool parse_specular(tinyxml2::XMLElement* model);
        bool parse_emission(tinyxml2::XMLElement* model);
        bool parse_ambient(tinyxml2::XMLElement* model);
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
