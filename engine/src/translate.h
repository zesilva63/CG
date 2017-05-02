#ifndef __TRANSLATE__
#define __TRANSLATE__

#include <tinyxml2.h>
#include <vector>
#include "../../src/vertex.h"
#include "operation.h"

class Translate : public Operation {
    public:
        Translate();
        void parse(tinyxml2::XMLElement *tr);
        void apply();
        const char* type();

        void add_point(tinyxml2::XMLElement *sc);
        void genCurve();
        void renderCurve();
    private:
        std::vector<Vertex*> points;
        std::vector<Vertex*> curve;
        float time;
        float x;
        float y;
        float z;
};

#endif
