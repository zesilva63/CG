#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <string>
#include <stdexcept>

class Vertex {
    private:
        float x;
        float y;
        float z;

    public:
        Vertex(float x, float y, float z);
        Vertex(float u, float v);
        Vertex(std::string);
        float getX();
        float getY();
        float getZ();
        static Vertex* sub(Vertex*, Vertex*);
        static Vertex* cross_product(Vertex*, Vertex*);
        static Vertex* normalize(Vertex* v);

        virtual ~Vertex(void);
};

#endif
