// Handles SDL events
#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

void change_cam_distance(double *cam_distance, double scroll_amount, double max, double min);
void toggle_control(bool *user_controlled, SDL_KeyCode keycode);
void move_cube(SDL_KeyCode keycode, double *x_angle, double *y_angle, double speed);

#endif // _HANDLERS_H_
