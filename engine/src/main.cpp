#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>

#include <stdio.h>
#include "scene.h"
#include "../../src/vertex.h"

using std::vector;

vector<Vertex*> vertices;

float alpha = 0;
float beta = 0;
float radius = 5;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderscene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    float px = radius * cos(beta) * sin(alpha);
    float py = radius * sin(beta);
    float pz = radius * cos(beta) * cos(alpha);

    gluLookAt(px, py, pz,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glBegin(GL_TRIANGLES);
    for(Vertex *v: vertices)
        glVertex3f(v->getX(), v->getY(), v->getZ());
    glEnd();

    // End of frame
    glutSwapBuffers();
}

void camera_motion(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': alpha -= 0.1;
                  break;
        case 'd': alpha += 0.1;
                  break;
        case 's': radius += 0.1;
                  break;
        case 'w': radius -= 0.1;
                  break;
        case 'j': beta -= 0.1;
                  break;
        case 'k': beta += 0.1;
                  break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    scene *s = new scene();

    if (argc == 1) {
        std::cout << "Input file required" << std::endl;
        return 1;
    }

    s->parse(argv[1]);
    vertices = s->get_vertices();

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Engine");

    // required callback registry
    glutDisplayFunc(renderscene);
    glutReshapeFunc(changeSize);

    // register keyboard callbacks
    glutKeyboardFunc(camera_motion);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
