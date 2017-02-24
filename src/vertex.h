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
        Vertex(std::string);
        float getX();
        float getY();
        float getZ();

        virtual ~Vertex(void);
};

#endif
