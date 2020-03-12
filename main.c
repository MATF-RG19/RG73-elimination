#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"

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
    glutFullScreen();
  
    /*Pozivanje funkcija za obradu dogadjaja*/
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
  
    /*OpenGL inicijalizacija*/
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    /*boja pozadine*/
    glClearColor(0.10,0.20,0.30, 0);
  
    /*Ukljucivanje svetla, i osvetljavanje scene*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);


    x_position=0;
    y_position=-0.6;
    z_position=0;
    man_radius=0.1;
    man_movement=0.05;

    left=-3;
    right=3;

    animation_ongoing=0;

    player_moving = false;
    left_pressed = false;
    right_pressed = false;

    glutMainLoop();
return 0;
}

void on_reshape(int width, int height){
    /*Podesava se sirina i visina*/
    window_width=width;
    window_height=height;
    
    /*Podesava se viewport*/
    glViewport(0,0,window_width, window_height);
    
    /*Podesava se projekcija*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   window_width/(float)window_height,
                   1,100);
    
}

void on_display(void){

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

    glPushMatrix();
        glTranslatef(x_position, y_position,z_position);
        drawMan();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
        drawGround();
    glPopMatrix();

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

void on_keyboard(unsigned char key, int x, int y){

    switch(key){
      case 27:
        exit(0);
        break;
      case 'g':
      case 'G':
        if(!running){
          glutDisplayFunc(on_display);
          glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          glutTimerFunc(0, on_timer, TIMER_ANIMATION);
          running=true;
          }
        break;
      case 'p':
      case 'P':
        if(running){
          running = false;
        }else{
          glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          glutTimerFunc(0, on_timer, TIMER_ANIMATION);
          running = true;
        }
        break;
      case 'r':
      case 'R':
        x_position=0;
        y_position=-0.6;
        z_position=0;
        man_radius=0.1;
        man_movement=0.05;

        animation_ongoing=0;

        player_moving = false;
        left_pressed = false;
        right_pressed = false;
        break;
      case 'a':
      case 'A':
        left_pressed = true;

        if(x_position - man_movement <= (left + man_radius *2.5 ))
          x_position=left + man_radius * 2.5;
        else{
          x_position -=man_movement;
        }

        animation_ongoing = 1;
         break;
     case 'd':
     case 'D':
        right_pressed = true;
        animation_ongoing = 1;

        if(x_position + man_movement >= (right - man_radius * 2.5))
        x_position = right - man_radius *2.5;
        else{
          x_position +=man_movement;
        }
        break;
    default:
        break;
    }
}

void on_keyboard_up(unsigned char key, int x, int y) {
  switch(key){
   case 'a':
   case 'A':
      left_pressed = false;
      animation_ongoing = 0;
       break;
   case 'd':
   case 'D':
     right_pressed = false;
     animation_ongoing = 0;
      break;
  default:
      break;
  }
}

void on_timer(int value)
{
    if (value != TIMER_ID && value != TIMER_ANIMATION)
        return;

    if(value == TIMER_ID) {
      glutPostRedisplay();
     
      if (running){
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
      }
    }else if(value == TIMER_ANIMATION) {

      if(animation_ongoing == 1) {
        animation_parameter += 0.1f;
      } else {
        animation_parameter = 0;
      }
      glutPostRedisplay();

      if (running){
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ANIMATION);
      }
    }
}
