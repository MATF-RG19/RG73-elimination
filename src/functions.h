#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BALLS_LEN 10

// Struktura za loptu
typedef struct Ball {
  double x, y;
  bool free;
} Ball;

#define TIMER_ID 0
#define TIMER_SPAWN_OBJECT_ID 1
#define TIMER_ANIMATION 2
#define TIMER_INTERVAL 20
#define SPAWN_INTERVAL 100

#define MAX_LIVES 3

//Teksture koje koristimo
#define FILENAME0 "../Textures/grass.bmp"
#define FILENAME1 "../Textures/building1.bmp"
#define FILENAME2 "../Textures/building2.bmp"
#define FILENAME3 "../Textures/lava.bmp"
#define FILENAME4 "../Textures/startgame.bmp"
#define FILENAME5 "../Textures/gameover.bmp"
#define FILENAME6 "../Textures/background.bmp"

// Deklaracije callback funkcija
extern void on_display(void);
extern void on_reshape(int width, int height);
extern void on_keyboard(unsigned char key, int x, int y);
extern void on_keyboard_up(unsigned char key, int x, int y);
extern void on_timer(int value);
extern void draw_start_screen(void);
extern void draw_end_screen(void);

extern void reset();

extern void draw_man();
extern void draw_text();
extern void draw_ball();
extern void draw_ground();
extern void draw_axes();

// Za teksture
extern void load_textures();
extern GLuint names[7];

int window_width, window_height;
double left_wall, right_wall, bottom_wall, top_wall;

// Promenljive za polozaj coveka
double x_position, y_position, z_position;
double man_radius;
double man_movement;
double man_height;

bool left_pressed;
bool right_pressed;
//da li pokusava da uhvati loptu
bool has_target;

float arms_angle;
int spawn_counter;

// Promenljive koje sluze za informacije o igri
bool animation_ongoing;
float animation_parameter;
bool running;
int score;
int lives;

#endif
