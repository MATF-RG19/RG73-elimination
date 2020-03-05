#include <GL/glut.h>
#include <stdlib.h>
#include "function.h"

static int window_width, window_height;

static void on_timer(int value);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv){
   /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    /* Ambijentalno osvetljenje scene. */
    GLfloat model_ambient[] = { 0.3, 0.3, 0.3, 1 };
   
    /*Inicijalizacija*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    /*Kreira se prozor*/
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Elimination");
  
    /*Pozivanje callback funkcija*/
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
  
    /*OpenGL inicijalizacija*/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.10,0.20,0.30, 0);
  
    /*Ukljucivanje svetla, i osvetljavanje scene*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);


    x_position=0;
    y_position=-1;
    z_position=0;

    glutFullScreen();
    glutMainLoop();
return 0;
}

static void on_reshape(int width, int height){
    window_width=width;
    window_height=height;
    
    glViewport(0,0,window_width, window_height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   window_width/(float)window_height,
                   1,100);
    
}

static void on_display(void){

   /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

   /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.5, 0.8, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0, 0, 0, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 15;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
 
    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    glTranslatef(x_position, y_position,z_position);
    drawMan();
    
    glDisable(GL_LIGHTING);
    drawGround();
    
       /*Koordinatni sistem
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
        */ 
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y){
   
    switch(key){
       case 27:
         exit(0);
         break;
    }
}
