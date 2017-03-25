#include <GL/glut.h>
#include <fstream>
#include <exception>
#include "ship.h"


void Ship::defineShip(){
    
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glPushMatrix();
    glScalef(0.2,0.2,0.2);
    	glPushMatrix(); //Main Deck
            glColor3f(0.5,0.5,0.5);
            glScalef(1, 0.5, 0.5);
            glutSolidCube(0.5);
        glPopMatrix();
        glPushMatrix(); //Main deck back-rigth
            glTranslated(0.1,0.1,0.7);
            glScalef(0.4, 0.4, 0.25);
            glutSolidCube(0.5);
        glPopMatrix();
        glPushMatrix(); //Main deck back-left
            glTranslated(-0.1,0.1,0.7);
            glScalef(0.4, 0.4, 0.25);
            glutSolidCube(0.5);
        glPopMatrix();
        glPushMatrix(); //side deck left
            glTranslated(-0.4,0,-0.1);
            glRotatef(40,0,0,1);
            glScalef(0.7, 0.3, 0.3);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //side deck rigth
            glTranslated(0.4,0,-0.1);
            glRotatef(-40,0,0,1);
            glScalef(0.7, 0.3, 0.3);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); // side deck left top
            glTranslated(-0.4,0,0);
            glRotatef(40,0,0,1);
            glScalef(0.6, 0.2, 0.2);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); // side deck rigth top
            glTranslated(0.4,0,0);
            glRotatef(-40,0,0,1);
            glScalef(0.6, 0.2, 0.2);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); // wings
            glTranslated(0,0,-0.2);
            glScalef(3.5, 0.05, 0.05);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); // main propolsor left
        	glColor3f(0.9,0.7,0.8);
            glTranslated(-0.5,-0.2,0.2);
            glScalef(0.25, 0.25, 0.25);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix();  // main propolsor rigth
            glTranslated(0.5,-0.2,0.2);
            glScalef(0.25, 0.25, 0.25);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix(); // main minor propolsor left
            glColor3f(0.8,0.2,0.2);
            glTranslated(-0.5,-0.2,0.4);
            glScalef(0.15, 0.15, 0.15);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix(); // main minor propolsor rigth
            glTranslated(0.5,-0.2,0.4);
            glScalef(0.15, 0.15, 0.15);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix();  // secundary propolsor rigth
            glTranslated(1.3,-0.03,0.2);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix(); // secundary propolsor left
            glTranslated(-1.3,-0.03,0.2);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(1,20,20);
        glPopMatrix();
        glPushMatrix(); //left top wing 
            glColor3f(0.1,0.2,0.8);
            glTranslated(-0.6,0.1,-0.2);
            glRotatef(120,0,0,1);
            glScalef(0.8, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //right top wing
            glTranslated(0.6,0.1,-0.2);
            glRotatef(-120,0,0,1);
            glScalef(0.8, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //left bottom wing
            glTranslated(-0.5,-0.3,-0.2);
            glRotatef(120,0,0,1);
            glScalef(0.8, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //right bottom wing
            glTranslated(0.5,-0.3,-0.2);
            glRotatef(-120,0,0,1);
            glScalef(0.8, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //left outter wing
            glTranslated(-1.45,0.1,-0.2);
            glRotatef(120,0,0,1);
            glScalef(0.3, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix(); //right outter wing
            glTranslated(1.45,0.1,-0.2);
            glRotatef(-120,0,0,1);
            glScalef(0.3, 0.1, 0.1);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
}