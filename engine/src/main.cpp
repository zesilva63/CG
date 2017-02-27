#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "scene.h"
#include "../../src/vertex.h"

using std::vector;

vector<Vertex*> vertices;

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
    gluLookAt(5,0,5,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glBegin(GL_TRIANGLES);
    for(Vertex *v: vertices)
        glVertex3f(v->getX(), v->getY(), v->getZ());
    glEnd();

    // End of frame
    glutSwapBuffers();
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
    glutCreateWindow("CG@DI-UM");

    // required callback registry
    glutDisplayFunc(renderscene);
    glutReshapeFunc(changeSize);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
