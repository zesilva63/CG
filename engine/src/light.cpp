#include <GL/glut.h>
#include "light.h"

using tinyxml2::XMLElement;

void Light::parse(XMLElement* model) {
    model->QueryFloatAttribute("posX", &pos[0]);
    model->QueryFloatAttribute("posY", &pos[1]);
    model->QueryFloatAttribute("posZ", &pos[2]);

    pos[3] = 0.0f;
    if (!strcmp(model->Attribute("type"), "POINT"))
        pos[3] = 1.0f;
}

void Light::render() {
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
