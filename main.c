#include <GL/glut.h>
#include <stdlib.h>


static int window_width, window_height;

static void on_timer(int value);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv){
   
    /*Inicijalizacija*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
  
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.23,0.45,0.12, 0);
  
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
 
   
       /*Koordinatni sistem*/
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
     
    
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y){
   
    switch(key){
       case 27:
         exit(0);
         break;
    }
}
