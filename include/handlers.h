// Handles SDL events
#include <SDL.h>
#include <stdbool.h>

void change_cam_distance(float *cam_distance, float scroll_amount, float max, float min);
void toggle_control(bool *user_controlled, SDL_KeyCode keycode);
void move_cube(SDL_KeyCode keycode, float *x_angle, float *y_angle, float speed);