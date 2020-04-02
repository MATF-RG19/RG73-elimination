#include <GL/glut.h>

#include "functions.h"

GLUquadric* sphere;

void draw_man(void){
  // ako su i levo i desno pritisnuti ne pomeramo igraca
  bool moving_left = left_pressed && !right_pressed;
  bool moving_right = right_pressed && !left_pressed;

    // okrecemo igraca na odgovarajucu stranu
     if(moving_left)
        glRotatef(-90, 0, 1, 0);
     else if(moving_right)
        glRotatef(90, 0, 1, 0);
    
    glShadeModel(GL_FLAT);
    // glava
    glPushMatrix();
        glColor3f(1,0.71,0.94);
        glTranslatef(0,0.4,0);
        glutSolidSphere(0.1, 100,100);
    glPopMatrix();
 
    // telo
    glPushMatrix();
        glColor3f(0.4,0,0.24);
        glTranslatef(0, 0.12, 0);
        glScalef(1.3,1.8,1);
        glutSolidCube(0.2);
    glPopMatrix();

    // noge
    glPushMatrix(); 
     glColor3f(0.50,0,0.50);
     // leva noga
     glPushMatrix();
         glTranslatef(-0.07,0,0);
         glRotatef(-40*sin(animation_parameter), 1, 0, 0);
         glTranslatef(0, -0.2, 0);
         glScalef(0.3, 1, 0.3);
         glutSolidCube(0.3);
     glPopMatrix();
     // desna noga
     glPushMatrix();
     glTranslatef(0.07, 0, 0);
     glRotatef(40*sin(animation_parameter), 1, 0, 0);
     glTranslatef(0, -0.2, 0);
     glScalef(0.3, 1, 0.3);
     glutSolidCube(0.3);     
     glPopMatrix();
    glPopMatrix(); 
   
    // ruke
    glPushMatrix(); 
     glColor3f(0.62,0.372,0.62);
     // desna ruka
     glPushMatrix();
        glTranslatef(-0.16, 0.2, 0);
        // ako je igrac blizu objekta i krece se onda rotiraj ruke ka objektu
        // ako je igrac blizu objekta i stoji samo podigni ruke
        // ako igrac nije blizu objekta onda animiraj kretanje ruku
        if(has_target){
            if(moving_right)
            glRotatef(arms_angle, 1, 0, 0);
            else if(moving_left)
            glRotatef(-arms_angle, 1, 0, 0);
            else
            glRotatef(180, 1, 0, 0);
        }else{
            glRotatef(60*sin(animation_parameter), 1, 0, 0);
        }
        glTranslatef(0, -0.12f, 0);
        glScalef(0.25, 1.1, 0.25);
        glutSolidCube(0.25);
     glPopMatrix();
     // leva ruka
     glPushMatrix();
        glTranslatef(0.16, 0.2 ,0);
        // ako je igrac blizu objekta i krece se onda rotiraj ruke ka objektu
        // ako je igrac blizu objekta i stoji samo podigni ruke
        // ako igrac nije blizu objekta onda animiraj kretanje ruku
        if(has_target){
            if(moving_right)
            glRotatef(arms_angle, 1, 0, 0);
            else if(moving_left)
            glRotatef(-arms_angle, 1, 0, 0);
            else
            glRotatef(180, 1, 0, 0);
        }else{
            glRotatef(-60*sin(animation_parameter), 1, 0, 0);
        }
        glTranslatef(0, -0.12f, 0);
        glScalef(0.25, 1.1, 0.25);
        glutSolidCube(0.25);
     glPopMatrix();
    glPopMatrix();
}

void draw_text() {
	// Crtamo tekst za zivote i poene
	char str[50];
	int len = 0;
	glColor3f(1,0,0);

  // cuvaj trenutne matrice i promeni projekciju na ortografsku
  // postavljamo ravni na velicinu ekrana
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushMatrix();
        glRasterPos2f(window_width-330, window_height-50);
        sprintf(str, "Lives: %d", lives);
        len = strlen(str);
        for (int i = 0; i < len; i++) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        }
    glPopMatrix();

    glPushMatrix();
        glRasterPos2f(250, window_height-50);
        sprintf(str, "Score: %d", score);
        len = strlen(str);
        for (int i = 0; i < len; i++) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        }
    glPopMatrix();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}
   
void draw_ball(){
    // Crtamo loptu i postavljamo teksturu na loptu
    sphere=gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glScalef(0.09,0.09,0.09);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, names[3]);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.0, 32, 16);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
}

void draw_ground() {
	// Iscrtavamo pod
	glPushMatrix();    
		glTranslatef(0, -1, 0);
		glColor3f(0.4,0.4,0.4);
		glScalef(100, 0, 40);
		glutSolidCube(1);
	glPopMatrix();
}

void draw_axes(){
   //Koordinatni sistem
     
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
        glVertex3f(0,0,0);
        glVertex3f(-100,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
        glVertex3f(0,0,0);
        glVertex3f(0,-100,0);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-100);
        glEnd(); 
 }       
 
