#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define TIMER_ID 0
#define TIMER_ANIMATION 2
#define TIMER_INTERVAL 20

/*Deklaracije callback funkcija*/
extern void on_display(void);
extern void on_reshape(int width, int height);
extern void on_keyboard(unsigned char key, int x, int y);
extern void on_keyboard_up(unsigned char key, int x, int y);
extern void on_timer(int value);

extern void drawMan();
extern void drawGround();

int window_width, window_height;

/*Ivice do kojih coveculjak moze da se krece*
Kasnije ce name koristiti za postavljanje tekstura*/
double left, right;

/*Promenljive za polozaj coveka*/
double x_position, y_position, z_position;
double man_radius;
double man_movement;
bool player_moving;
bool left_pressed;
bool right_pressed;

/*Promenljive koje sluze za informacije o igri*/
int animation_ongoing;
float animation_parameter;
bool running;

#endif