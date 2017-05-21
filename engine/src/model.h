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
        float *normalData;
        float *textureData;
        std::vector<Vertex*> vertices;
        double red, green, blue;
        void parse_line(std::string line);
        void loadTexture(std::string s);
        void parse_material(tinyxml2::XMLElement* model);
        void parse_texture(std::string directory, tinyxml2::XMLElement* model);
        void render_material();
        double n;
        int vertexI = 0;
        int normalI = 0;
        int textureI = 0;
        GLuint vertex[1];
        GLuint normal[1];
        GLuint texture[1];
        GLuint texID;
        float ambient[4] = {0.2, 0.2, 0.2, 1};
        float diffuse[4] = {0.8, 0.8, 0.8, 1};
        float specular[4] = {0, 0, 0, 1};
        float emission[4] = {0, 0, 0, 1};
        float shininess;
        GLenum light_type;
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
