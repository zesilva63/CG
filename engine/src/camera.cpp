#include <string.h>
#include <GL/glut.h>
#include <fstream>
#include <exception>
#include <math.h>
#include "camera.h"

#define _X 0
#define _Y 1
#define _Z 2

#define SPEED 0.04

static void cross(float *a, float *b, float *r);

Camera::Camera() {
    memset(keys, 0, sizeof(bool) * 256);

    deltaX = 0.0;
    deltaY = 0.0;

    yOrigin = -1;
    xOrigin = -1;

    up[_X] = 0;
    up[_Y] = 1;
    up[_Z] = 0;

    px = py = 0;
    pz = 15;

    lx = ly = lz = 0;
}

void Camera::key_down(unsigned int key) {
    keys[key] = true;
}

void Camera::key_up(unsigned int key) {
    keys[key] = false;
}

void Camera::mouse_button(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            angle += deltaX;
            xOrigin = -1;
        } else {
            xOrigin = x;
        }
    }
}

void Camera::mouse_move(int x, int y) {
    if (xOrigin >= 0) {
        printf("DISTANCE: %d DELTA: %f\n", x - xOrigin, (x-xOrigin) * 0.001f);
        deltaX = (x - xOrigin) * 0.001f;

        printf("LZ: %f DZ: %f ANGLE: %f\n", lz, dz, angle + deltaX);
        lx = dx * sin(angle + deltaX);
        lz = - dz * cos(angle + deltaX);
        printf("LZ: %f\n", lz);

        update_direction();
    }
}

void Camera::update(float *v, int s) {
    px += s * v[_X] * SPEED;
    pz += s * v[_Z] * SPEED;

    lx += s * v[_X] * SPEED;
    lz += s * v[_Z] * SPEED;
}

void Camera::move_to_camera(bool backwards) {
    int direction = (backwards) ? -1 : 1;

    printf("%f %f %f\n", px, lx, dx);
    printf("%f %f %f\n", pz, lz, dz);
    px += direction * dx * SPEED;
    pz += direction * dz * SPEED;

    lx += direction * dx * SPEED;
    lz += direction * dz * SPEED;
}

/* void Camera::update_aux(float *r) { */
/*     cross(d, up, r); */
/* } */

void Camera::update_direction() {
    dx = lx - px;
    dy = 0;
    dz = lz - pz;
}

void Camera::apply() {
    float d[3], r[3];
    update_direction();

    if (keys['w']) {
        move_to_camera(false);
        update_direction();
    }

    /* if (keys['a']) { */
    /*     update(r, -1); */
    /*     update_aux(d, r); */
    /* + */

    if (keys['s']) {
        move_to_camera(true);
        update_direction();
    }

    /* if (keys['d']) { */
    /*     update(r, 1); */
    /*     update_aux(d, r); */
    /* } */
}

void Camera::view() {
    apply();
    gluLookAt(px, py, pz,
              lx, py, lz,
              0, 1, 0);
}

static void cross(float *a, float *b, float *r) {
    r[0] = a[1]*b[2] - a[2]*b[1];
	r[1] = a[2]*b[0] - a[0]*b[2];
	r[2] = a[0]*b[1] - a[1]*b[0];
}
