#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <IL/il.h>

#include <exception>
#include "view.h"
#include "camera.h"
#include "../../src/vertex.h"

using std::vector;

View scene;
View ship;
Camera c;

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

    glTranslatef(0.0f, -0.6f, -3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ship.render();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* glRotatef(180,1.0,0.0,0.0); */
    /* glTranslatef(0.0f, 00.f, 30); */

    c.view();
    scene.render_lights();
    scene.render();

    // End of frame
    glutSwapBuffers();
}

void key_up(unsigned char key, int x, int y) {
    c.key_up(key);
}

void key_down(unsigned char key, int x, int y) {
    c.key_down(key);
}

void mouse_button(int button, int state, int x, int y) {
    c.mouse_button(button, state, x, y);
}

void mouse_move(int x, int y) {
    c.mouse_move(x, y);
}

int main(int argc, char **argv) {

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Engine");
    glewInit();

    // required callback registry
    glutDisplayFunc(renderscene);
    glutIdleFunc(renderscene);
    glutReshapeFunc(changeSize);

    // register keyboard callbacks
    glutKeyboardFunc(keyboard);

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    try {
        switch(argc) {
            case 1: std::cerr << "Input file required" << std::endl;
                    return 1;
            case 2: scene.parse(std::string(argv[1]));
                    break;
            default: scene.parse(std::string(argv[1]));
                     ship.parse(std::string(argv[2]));
        }
    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 2;
    }

    c = Camera();

    // required callback registry
    glutDisplayFunc(renderscene);
    glutIdleFunc(renderscene);
    glutReshapeFunc(changeSize);

    // register keyboard callbacks
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    glutMouseFunc(mouse_button);
    glutMotionFunc(mouse_move);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
