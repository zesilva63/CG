#include <GL/glut.h>
#include "light.h"

using tinyxml2::XMLElement;

void Light::turnOn(){
	glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	GLfloat amb[4]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat diff[4] = {0.8, 0.8, 0.8, 1.0};
    GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 50.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();
}

void Light::parse(XMLElement* model) {
    model->QueryFloatAttribute("posX", &pos[0]);
    model->QueryFloatAttribute("posY", &pos[1]);
    model->QueryFloatAttribute("posZ", &pos[2]);

    pos[3] = 0.0f;
    if (!strcmp(model->Attribute("type"), "POINT"))
        pos[3] = 0.0f;
}
