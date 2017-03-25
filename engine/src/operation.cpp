#include <GL/glut.h>
#include "operation.h"

using tinyxml2::XMLElement;

Translation::Translation() {
    x = 0;
    y = 0;
    z = 0;
}

Rotation::Rotation() {
    angle = 0;
    axisX = 0;
    axisY = 0;
    axisZ = 0;
}

Scaling::Scaling() {
    x = 1;
    y = 1;
    z = 1;
}

void Translation::parse(XMLElement *tr) {
    tr->QueryDoubleAttribute("X", &x);
    tr->QueryDoubleAttribute("Y", &y);
    tr->QueryDoubleAttribute("Z", &z);
}

void Rotation::parse(XMLElement *rt) {
    rt->QueryDoubleAttribute("angle", &angle);
    rt->QueryDoubleAttribute("axisX", &axisX);
    rt->QueryDoubleAttribute("axisY", &axisY);
    rt->QueryDoubleAttribute("axisZ", &axisZ);
}

void Scaling::parse(XMLElement *sc) {
    sc->QueryDoubleAttribute("X", &x);
    sc->QueryDoubleAttribute("Y", &y);
    sc->QueryDoubleAttribute("Z", &z);
}

void Translation::apply() {
    glTranslatef(x, y, z);
}

void Rotation::apply() {
    glRotatef(angle, axisX, axisY, axisZ);
}

void Scaling::apply() {
    glScalef(x, y, z);
}