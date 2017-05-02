#include <GL/glut.h>
#include "scale.h"

using tinyxml2::XMLElement;

Scale::Scale() {
    x = 1;
    y = 1;
    z = 1;
}

void Scale::parse(XMLElement *sc) {
    sc->QueryDoubleAttribute("X", &x);
    sc->QueryDoubleAttribute("Y", &y);
    sc->QueryDoubleAttribute("Z", &z);
}

void Scale::apply() {
    glScalef(x, y, z);
}

const char* Scale::type() {
    return "scale";
}

