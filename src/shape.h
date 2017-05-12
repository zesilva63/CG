#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <vector>
#include <fstream>

#include "vertex.h"

class Shape {
    private:
        std::vector<Vertex*> vertices;
        std::vector<Vertex*> normals;
        std::vector<Vertex*> texture;

    public:
        Shape(std::vector<Vertex*> vertices, std::vector<Vertex*> normals, std::vector<Vertex*> texture);
        Shape();
        Shape(std::string file_path);
        void get_vertex(int i, Vertex** vertex, Vertex** normal, Vertex** texture);
        void push_vertex(Vertex* v);
        void push_normal(Vertex* n);
        void push_texture(Vertex* t);
        void push_shape(Shape* s);
        void reverse();
        int size();

        virtual ~Shape(void);
};

#endif
