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
    GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}
