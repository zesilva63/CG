#include <GL/glut.h>
#include "translate.h"
#include <math.h>

using tinyxml2::XMLElement;
using std::vector;

static void getCatmullRomPoint(float t, int *indices, float *res, vector<Vertex*> transpontos);
static void getGlobalCatmullRomPoint(float gt, float *res, vector<Vertex*> transpontos);

Translate::Translate() {
    x = 0;
    y = 0;
    z = 0;
    time = -1;
}

void Translate::parse(XMLElement *tr) {
    tr->QueryFloatAttribute("X", &x);
    tr->QueryFloatAttribute("Y", &y);
    tr->QueryFloatAttribute("Z", &z);
    tr->QueryFloatAttribute("time", &time);
}

void Translate::add_point(XMLElement *pt){
    double x,y,z;
    pt->QueryDoubleAttribute("X", &x);
    pt->QueryDoubleAttribute("Y", &y);
    pt->QueryDoubleAttribute("Z", &z);
    points.push_back(new Vertex(x,y,z));
}

const char* Translate::type() {
    return "translate";
}

void Translate::apply() {
    float res[3] = { x, y, z };

    if (time > 0) {
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
        float t_relative = elapsed / (time * 1000);

        getGlobalCatmullRomPoint(t_relative, res, points);
    }

    glTranslatef(res[0], res[1], res[2]);
}

void Translate::genCurve() {
    float res[3];

    for (float gt = 0; gt < 1; gt += 0.01){
        getGlobalCatmullRomPoint(gt, res, points);
        curve.push_back(new Vertex(res[0], res[1], res[2]));
    }
}

void Translate::renderCurve() {
	float p[3];

	glBegin(GL_LINE_LOOP);
    for (Vertex *v: curve) {
		p[0] = v->getX();
		p[1] = v->getY();
		p[2] = v->getZ();
		glVertex3fv(p);
	}
	glEnd();
}

void getGlobalCatmullRomPoint(float gt, float *res, vector<Vertex*> transpontos) {
    float t = gt * transpontos.size(); // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + transpontos.size() - 1) % transpontos.size();
    indices[1] = (indices[0] + 1) % transpontos.size();
    indices[2] = (indices[1] + 1) % transpontos.size();
    indices[3] = (indices[2] + 1) % transpontos.size();

    getCatmullRomPoint(t, indices, res, transpontos);
}

void getCatmullRomPoint(float t, int *indices, float *res, vector<Vertex*> transpontos) {
    float res_aux[4];

    float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
                      {  1.0f, -2.5f,  2.0f, -0.5f },
                      { -0.5f,  0.0f,  0.5f,  0.0f },
                      {  0.0f,  1.0f,  0.0f,  0.0f } };

    res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
    float t3 = t*t*t, t2 = t*t;

    //T*M
    res_aux[0] = t3*m[0][0] + t2*m[1][0] + t*m[2][0] + m[3][0];
    res_aux[1] = t3*m[0][1] + t2*m[1][1] + t*m[2][1] + m[3][1];
    res_aux[2] = t3*m[0][2] + t2*m[1][2] + t*m[2][2] + m[3][2];
    res_aux[3] = t3*m[0][3] + t2*m[1][3] + t*m[2][3] + m[3][3];

    int i0 = indices[0]; Vertex * p0 = transpontos[i0];
    int i1 = indices[1]; Vertex * p1 = transpontos[i1];
    int i2 = indices[2]; Vertex * p2 = transpontos[i2];
    int i3 = indices[3]; Vertex * p3 = transpontos[i3];

    //T*M*P = res
    res[0] = res_aux[0] * p0->getX() + res_aux[1] * p1->getX() + res_aux[2] * p2->getX() + res_aux[3] * p3->getX();
    res[1] = res_aux[0] * p0->getY() + res_aux[1] * p1->getY() + res_aux[2] * p2->getY() + res_aux[3] * p3->getY();
    res[2] = res_aux[0] * p0->getZ() + res_aux[1] * p1->getZ() + res_aux[2] * p2->getZ() + res_aux[3] * p3->getZ();
}
