#include <GL/glut.h>
#include "function.h"

void drawMan(void){
    glShadeModel(GL_FLAT);
      /*glava*/
    glPushMatrix();
        glColor3f(1,0.71,0.94);
        glTranslatef(0,0.3,0);
        glutSolidSphere(0.1, 100,100);
    glPopMatrix();
 
   /*telo*/
    glPushMatrix();
        glColor3f(0.4,0,0.24);
        glScalef(1,1.5,1);
        glutSolidCube(0.3);
    glPopMatrix();

  /*noge*/
  glPushMatrix(); 
     glColor3f(0.501,0,0.501);
    /*leva noga*/
     glPushMatrix();
         glTranslatef(-0.09,-0.35,0);
         glScalef(0.25, 1, 0.25);
         glutSolidCube(0.25);
      glPopMatrix();
 /*desna noga*/
   glPushMatrix();
       glTranslatef(0.05,-0.35,0);
       glScalef(0.25, 1, 0.25);
       glutSolidCube(0.25);
   glPopMatrix();
 glPopMatrix(); 
   
 /*ruke*/
  glPushMatrix(); 
    glColor3f(0.623,0.372,0.623);
    /*leva ruka*/
     glPushMatrix();
         glTranslatef(-0.18,0,0);
         glScalef(0.25, 1.3, 0.25);
         glutSolidCube(0.17);
      glPopMatrix();
 /*desna ruka*/
   glPushMatrix();
       glTranslatef(0.18,0,0);
       glScalef(0.25, 1.3, 0.25);
       glutSolidCube(0.17);
   glPopMatrix();
 glPopMatrix();
}

void drawGround() {
	/*Iscrtavamo pod*/
	glPushMatrix();    
		glTranslatef(0, -1, 0);
		glColor3f(0.4,0.4,0.4);
		glScalef(100, 0, 40);
		glutSolidCube(1);
	glPopMatrix();
}