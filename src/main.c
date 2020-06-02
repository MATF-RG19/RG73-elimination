/*
Projekat iz Racunarske grafike: Jovana Markovic 144/2017
Napomene:
1. Postavljanje osvetljenja nauceno na casu, iskorisceno gradivo sa casa, postavljeni drugi parametri tako da odgovaraju mom projektu
2. Biblioteka za teksture preuzeta sa casa
3. Postavljanje teksture za loptu nadjeno na internetu
4. Neke slike za teksture preuzete od drugih kolega (tj. slike tekstura za nebo i zgrade preuzete od koleginice ciji je projekat RG135-rooftop-runner)
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"
#include "image.h"

//Niz lopti koje padaju
Ball balls[BALLS_LEN];

// Niz u koji smestamo teksture
GLuint names[7];

int main(int argc, char **argv){
    // Ambijentalna, difuzna, spekularna boja svetla redom
    GLfloat light_ambient[] = { 0, 0, 0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    // Ambijentalno osvetljenje scene.
    GLfloat model_ambient[] = { 0.3, 0.3, 0.3, 1 };
   
    // Inicijalizacija
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    // Kreira se prozor
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Elimination");
    glutFullScreen();
  
    // Teksture koje cu koristiti
    load_textures();
    
    // Pozivanje funkcija za obradu dogadjaja
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(draw_start_screen);
  
    // OpenGL inicijalizacija
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    // Generisanje seeda za objekte
    srand(time(NULL));
  
    // Boja pozadine
    glClearColor(0.08,0.30,0.35, 0);
  
    // Ukljucivanje svetla, i osvetljavanje scene
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    x_position=0;
    y_position=-1;
    z_position=0;
    man_radius=0.25;
    man_height=0.58;
    man_movement=1.5;

    left_wall=-2.8;
    right_wall=2.8;
    bottom_wall=-1.4;
    top_wall=2.5;
    
    
    animation_ongoing=false;
    gameover=false;
    animation_parameter=0;

    has_target=false;
    arms_angle=0;
    
    reset();

    left_pressed = false;
    right_pressed = false;
    
    glutMainLoop();
return 0;
}

void on_reshape(int width, int height){
    // Podesava se sirina i visina
    window_width=width;
    window_height=height;
    
    // Podesava se viewport
    glViewport(0,0,window_width, window_height);
    
    // Podesava se projekcija
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
                   (float)window_width/(float)window_height,
                   1,100);
    
    glutPostRedisplay();
}

void on_display(void){

    // Ambijentalna, difuzna, spekularna boja svetla redom
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1 };

    // Koeficijenti ambijentalne, difuzne, spekularne refleksije materijala redom
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.0, 0.5, 0.8, 1 };
    GLfloat specular_coeffs[] = { 0, 0, 0, 1 };

    // Koeficijent glatkosti materijala.
    GLfloat shininess = 15;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
 
    // Ispisuje se tekst za zivot i poene
    glDisable(GL_LIGHTING);
    draw_text();
    
    // Ukljucuje se osvjetljenje i podesavaju parametri svetla.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Podesavaju se parametri materijala.
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //Teksture
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
	
    // nebo
	glBindTexture(GL_TEXTURE_2D, names[6]);
	glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(0, 0);
    glVertex3f(left_wall-2, bottom_wall-1, -1);

    glTexCoord2f(1, 0);
    glVertex3f(right_wall+2, bottom_wall-1, -1);

    glTexCoord2f(1, 1);
    glVertex3f(right_wall+2, top_wall+2, -1);

    glTexCoord2f(0, 1);
    glVertex3f(left_wall-2, top_wall+2, -1);
    glEnd();
  
    // leva zgrada
    glBindTexture(GL_TEXTURE_2D,names[1]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(0, 0);
    glVertex3f(left_wall, bottom_wall, 1);

    glTexCoord2f(1, 0);
    glVertex3f(left_wall, bottom_wall, -1);

    glTexCoord2f(1, 1);
    glVertex3f(left_wall, top_wall, -1);

    glTexCoord2f(0, 1);
    glVertex3f(left_wall, top_wall, 1);
    glEnd();
  
    // desna zgrada
    glBindTexture(GL_TEXTURE_2D,names[2]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(0, 0);
    glVertex3f(right_wall, bottom_wall, -1);

    glTexCoord2f(1, 0);
    glVertex3f(right_wall, bottom_wall, 1);

    glTexCoord2f(1, 1);
    glVertex3f(right_wall, top_wall, 1);

    glTexCoord2f(0, 1);
    glVertex3f(right_wall, top_wall, -1);
    glEnd();

    // trava
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(0, 0);
    glVertex3f(left_wall, bottom_wall, 1);

    glTexCoord2f(1, 0);
    glVertex3f(right_wall, bottom_wall, 1);

    glTexCoord2f(1, 1);
    glVertex3f(right_wall, bottom_wall, -1);

    glTexCoord2f(0, 1);
    glVertex3f(left_wall, bottom_wall, -1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Igrac
    glPushMatrix();
        glTranslatef(x_position, y_position,z_position);
        draw_man();
    glPopMatrix();
   
   /*Posto smo postavili teksturu za travu, vise nam ne treba pod
    glPushMatrix();
        draw_ground();
    glPopMatrix();
   */
   
    // Lopte
    for(int i = 0; i < BALLS_LEN; i++) {
      if(!balls[i].free) {
        glPushMatrix();
          glTranslatef(balls[i].x, balls[i].y, 0);
          if(balls[i].type==0){
            draw_bed_ball();
          } else if(balls[i].type==1){
            draw_ball1();
          } else if(balls[i].type==2){
            draw_ball2();
          } else if(balls[i].type==3){
            draw_ball3();
          }        
        glPopMatrix();
      }
    }
    
       /*Koordinatni sistem
        draw_axes();
        */
    
    glutSwapBuffers();
}

void on_keyboard(unsigned char key, int x, int y){

    switch(key){
      case 27:
        exit(0);
        break;
      // pokreni  
      case 'g':
      case 'G':
        if(!running){
          reset();
          
          gameover=false;
          x_position=0;
          y_position=-1;
          z_position=0;
        
          gameover=false;
          glutDisplayFunc(on_display);
          glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
          glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_SPAWN_OBJECT_ID);
          glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ANIMATION);
          running=true;
          }
        break;
      //resetuj  
      case 'r':
      case 'R':
        gameover=false;
        x_position=0;
        y_position=-1;
        z_position=0;
        man_radius=0.25;
        man_height=0.58;
        man_movement=1.5;

        animation_ongoing=false;
        animation_parameter=0;
        has_target=false;
        arms_angle=0;

        reset();
        
        left_pressed = false;
        right_pressed = false;
        
        break;
      // levo
      case 'a':
      case 'A':
        left_pressed = true;
        if(!right_pressed){
          animation_ongoing = true;
        }else{
          animation_ongoing = false;
          animation_parameter = 0;
        }
        break;
      // desno
      case 'd':
      case 'D':
        right_pressed = true;
        if(!left_pressed){
          animation_ongoing = true;
        }else{
          animation_ongoing = false;
          animation_parameter = 0;
        }
        break;
    default:
        break;
    }
}

void on_keyboard_up(unsigned char key, int x, int y){
  switch(key){
   case 'a':
   case 'A':
      left_pressed = false;
      if(!right_pressed){
        animation_ongoing = false;
      }else{
        animation_ongoing = true;
        animation_parameter = 0;
      }
       break;
   case 'd':
   case 'D':
      right_pressed = false;
      if(!left_pressed){
        animation_ongoing = false;
      }else{
        animation_ongoing = true;
        animation_parameter = 0;
      }
      break;
  default:
      break;
  }
}



void on_timer(int data){

  switch(data){
    case TIMER_ID:
      // Azuriraj objekte
      for(int i = 0; i < BALLS_LEN; i++){
        // Azuriramo samo postojece objekte
        if(!balls[i].free) {
          // Move the object
          balls[i].y -= 0.02f;

          // Kolizija sa igracem         
          if(fabs(x_position-balls[i].x)<man_radius && y_position+man_height>balls[i].y){
            balls[i].free = true;

            if(balls[i].type==0){
            score -=5;
            }
            else if(balls[i].type==1){
              score++;
            }else if(balls[i].type==2){
              score += 5;
            }else if(balls[i].type==3){
              score +=10;
            }
            continue;
          }

          // Oslobodimo objekat kada dovoljno padne
          if(balls[i].y < -1.5f){
            lives--;
            balls[i].free = true;
          }
        }
      }
    if(!gameover){
      // ako su oba dugmeta pritisnuta ne pomeramo igraca
      bool moving_left = left_pressed && !right_pressed;
      bool moving_right = right_pressed && !left_pressed;

      // Pomera se igrac
      if(moving_left){
        x_position -= man_movement * (double)TIMER_INTERVAL/1000;
        if(x_position <= (left_wall + man_radius * 2.5 ))
          x_position = left_wall + man_radius * 2.5;
      }
      if(moving_right){
        x_position += man_movement * (double)TIMER_INTERVAL/1000;
        if(x_position > (right_wall - man_radius * 2.5 ))
          x_position = right_wall - man_radius * 2.5;
      }

      // Pronadji najblizi objekat, pod uslovom da je dovoljno blizu
      int closest = -1;
      float min_dist = 5.0;
      float dist;
      for(int i = 0; i < BALLS_LEN; i++){
        if(!balls[i].free){
          if((moving_left && balls[i].x<=x_position) || (moving_right && balls[i].x>=x_position) || (fabs(balls[i].x-x_position)<=man_radius)) {
            dist = (x_position-balls[i].x)*(x_position-balls[i].x) + (y_position-balls[i].y)*(y_position-balls[i].y);
            if(dist < min_dist){
              min_dist = dist;
              closest = i;
            }
          }
        }
      }
    
      // Ako postoji objekat dovoljno blizu oznaci da igraca podize ruke i postavi ugao
      if(closest != -1){
        has_target = true;
        arms_angle = -90-atan2(balls[closest].y-y_position, balls[closest].x-x_position)*360/(2*3.14);
      }else{
        has_target = false;
      }
    }
      // Da li je igrac jos ziv
      if(lives <= 0){
        gameover = true;
        glutTimerFunc(GAME_OVER_INTERVAL, on_timer, TIMER_GAME_OVER_ID);
      }

      glutPostRedisplay();

      if (running){
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
      }
      break;
    case TIMER_SPAWN_OBJECT_ID:
      // Ne koristimo dugacak tajmer za ovo nego uvecavamo brojacku promenljivu
      // kako bi mogli uspesno da pauziramo igricu
      // inace svaki put kada pauziramo na manje od 2 sekunde pocelo bi da pada duplo vise lopti
      if (running){
        spawn_counter++;
        if(spawn_counter==SPAWN_INTERVAL){
          // Trazimo slobodan slot za objekat
          for(int i = 0; i < BALLS_LEN; i++){
            if(balls[i].free){
              // Postavljamo x poziciju objekta izmedju zgrada
              balls[i].x = left_wall + man_radius*2.5 + (right_wall-left_wall-2*man_radius*2.5)*(float)rand()/RAND_MAX;
              // Postavljamo y poziciju objekta iznad ekrana
              balls[i].y = 2.0f;
              //Postavljamo tip
              balls[i].type=rand()%BROJ_TIPOVA;
              // Oznacimo objekat da je alociran
              balls[i].free = false;
              break;
            }
          }
          spawn_counter = 0;
        }
        
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_SPAWN_OBJECT_ID);
      }
      break;
    case TIMER_ANIMATION:
      if(animation_ongoing == 1){
        animation_parameter += 0.1f;
      }else{
        animation_parameter = 0;
      }

      if(gameover){
        gameover_parameter += 0.04;
        if(gameover_parameter >= 1)
          gameover_parameter = 1;
      }else{
        gameover_parameter = 0;
      }

      glutPostRedisplay();

      if(running){
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ANIMATION);
        break;
      }
      case TIMER_GAME_OVER_ID:
        running = false;
        glutDisplayFunc(draw_end_screen);
        glutPostRedisplay();
      break;
  }
}

void reset(){
  score = 0;
  lives = MAX_LIVES;
  for(int i = 0; i < BALLS_LEN; i++){
    balls[i].free = true;
    balls[i].type=0;
  }
  spawn_counter=0;
}

void draw_start_screen(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3.5, 0,
              0, 0, 0,
              1, 0, 0);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, names[4]);

		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-2, 0, -4);

			glTexCoord2f(0, 1);
			glVertex3f(2, 0, -4);

			glTexCoord2f(1, 1);
			glVertex3f(2, 0, 4);

			glTexCoord2f(1, 0);
			glVertex3f(-2, 0, 4);
		glEnd();

	glDisable(GL_TEXTURE_2D);

    animation_ongoing=0;
    glutSwapBuffers();

}

void draw_end_screen(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3.5, 0,
              0, 0, 0,
              1, 0, 0);

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, names[5]);

		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-2, 0, -4);

			glTexCoord2f(0, 1);
			glVertex3f(2, 0, -4);

			glTexCoord2f(1, 1);
			glVertex3f(2, 0, 4);

			glTexCoord2f(1, 0);
			glVertex3f(-2, 0, 4);
		glEnd();

	glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();

}
