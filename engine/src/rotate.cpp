#include <GL/glut.h>
#include "rotate.h"

using tinyxml2::XMLElement;

Rotate::Rotate() {
    time = -1;
    angle = 0;
    axisX = 0;
    axisY = 0;
    axisZ = 0;
}

void Rotate::parse(XMLElement *rt) {
    rt->QueryFloatAttribute("time", &time);
    rt->QueryFloatAttribute("angle", &angle);
    rt->QueryFloatAttribute("axisX", &axisX);
    rt->QueryFloatAttribute("axisY", &axisY);
    rt->QueryFloatAttribute("axisZ", &axisZ);
}

void Rotate::apply() {
    float rot_value = angle;

    if (time > 0) {
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
        rot_value = (elapsed * 360) / (time * 1000);
    }

    glRotatef(rot_value, axisX, axisY, axisZ);
}

const char* Rotate::type() {
    return "rotate";
}
