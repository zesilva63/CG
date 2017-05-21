#include <GL/glut.h>
#include "rotate.h"

using tinyxml2::XMLElement;

Rotate::Rotate() {
    time = 0;
    axisX = 0;
    axisY = 0;
    axisZ = 0;
}

int Rotate::parse(XMLElement *rt) {
    rt->QueryFloatAttribute("time", &time);
    rt->QueryFloatAttribute("axisX", &axisX);
    rt->QueryFloatAttribute("axisY", &axisY);
    rt->QueryFloatAttribute("axisZ", &axisZ);
    if (time==0) return 0;
    return 1;
}

void Rotate::apply() {
    float r = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
    float gr = (r * 360) / (time * 1000);
    glRotatef(gr, axisX, axisY, axisZ);
}

const char* Rotate::type() {
    return "rotate";
}