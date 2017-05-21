#ifndef __ROTATE__
#define __ROTATE__

#include <tinyxml2.h>
#include <vector>
#include "../../src/vertex.h"


class Rotate{
    public:
        Rotate();
        int parse(tinyxml2::XMLElement *tr);
        void apply();
        const char* type();
    private:
        float time;
        float axisX;
        float axisY;
        float axisZ;
        
};

#endif