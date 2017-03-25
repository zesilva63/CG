#include <GL/glut.h>
#include <fstream>
#include <exception>
#include <math.h>
#include "camera.h"


float xrot = 0, yrot = 0, xpos = 0, zpos = -30, ypos = 0; 


void Camera::camera_motion(unsigned char key, int x, int y) {
	int i;
    switch (key) {
        case 'i': if(xrot < 45) xrot +=5;
                  if (xrot >360) xrot -= 360;
                  break;
        case 'k': if(xrot > -45) xrot-=5;
                  if (xrot < -360) xrot += 360;
                  break;
        case 'l': yrot +=5;
                  if (yrot >360) yrot -= 360;
                  break;
        case 'j': yrot-=5;
                  if (yrot < -360) yrot += 360;
                  break;
        case'a': xpos -=cos(yrot /180 * 3.141592653589793);
                 zpos -=sin(yrot /180 * 3.141592653589793);
                 break;

        case'd': xpos +=cos(yrot /180 * 3.141592653589793);
                 zpos +=sin(yrot /180 * 3.141592653589793);
                 break;

        case'w': zpos +=cos(yrot /180 * 3.141592653589793);
                 xpos -=sin(yrot /180 * 3.141592653589793);
                 ypos +=sin(xrot /180 * 3.141592653589793);
                 break;

        case's': zpos -=cos(yrot /180 * 3.141592653589793);
                 xpos +=sin(yrot /180 * 3.141592653589793);
                 ypos -=sin(xrot /180 * 3.141592653589793);
                 break;
    }
    glutPostRedisplay();
}

float Camera::getXPos(){
	return xpos;
}

float Camera::getYPos(){
	return ypos;
}

float Camera::getZPos(){
	return zpos;
}

float Camera::getXRot(){
	return xrot;
}

float Camera::getYRot(){
	return yrot;
}

void Camera::setXPos(float x){
	xpos = x;
}

void Camera::setYPos(float y){
	ypos = y;
}

void Camera::setZPos(float z){
	zpos = z;
}

void Camera::setXRot(float x){
	xrot = x;
}

void Camera::setYRot(float y){
	yrot = y;
}
