#ifndef __TRANSLATE__
#define __TRANSLATE__

#include <tinyxml2.h>
#include <vector>
#include "../../src/vertex.h"

class Translate{
    public:
        Translate();
        void parse(tinyxml2::XMLElement *sc);
        void apply();
        void add_point(tinyxml2::XMLElement *sc);
        std::vector<Vertex*> execCurvas();
        const char* type();
    private:
        double time;
        std::vector<Vertex*> points;
        void getGlobalCatmullRomPoint(float gt, float *res, std::vector<Vertex*> transpontos);
        void getCatmullRomPoint(float t,int *indices, float *res, std::vector<Vertex*> transpontos);
};

#endif