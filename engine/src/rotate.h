#ifndef __ROTATE__
#define __ROTATE__

#include <tinyxml2.h>
#include "operation.h"

class Rotate : public Operation {
    public:
        Rotate();
        void apply();
        void parse(tinyxml2::XMLElement *rt);
        const char* type();
    private:
        float time;
        float angle;
        float axisX;
        float axisY;
        float axisZ;
};

#endif
