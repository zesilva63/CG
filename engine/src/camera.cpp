#include <string.h>
#include <GL/glut.h>
#include <fstream>
#include <exception>
#include <math.h>
#include "camera.h"

Camera::Camera() {
    ypos = 0;
    xpos = zpos = -10;
    look_at_y = look_at_z = look_at_x = 0;

    memset(keys, 0, sizeof(bool)*256);
}

void Camera::key_down(unsigned int key) {
    keys[key] = true;
}

void Camera::key_up(unsigned int key) {
    keys[key] = false;
}

void Camera::apply() {
    if (keys['w']) {
        zpos += 0.6;
        look_at_z += 0.6;
    }

    if (keys['a']) {
        xpos += 0.6;
        look_at_x += 0.6;
    }

    if (keys['s']) {
        zpos -= 0.6;
        look_at_z -= 0.6;
    }

    if (keys['d']) {
        xpos -= 0.6;
        look_at_x -= 0.6;
    }
}

void Camera::view() {
    apply();
    gluLookAt(xpos, ypos, zpos,
              look_at_x, ypos, look_at_z,
              0, 1, 0);
}
