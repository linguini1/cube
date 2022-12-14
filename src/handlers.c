// Handles SDL events
#include "handlers.h"

#define TOLERANCE 0.05f

void change_cam_distance(float *cam_distance, float scroll_amount, float max, float min) {

    float amount = *cam_distance + 0.1f * scroll_amount;

    // Only increase if less than max allowed
    // Only decrease if greater than min allowed
    if (amount < max - TOLERANCE && amount > min + TOLERANCE) {
        *cam_distance = amount;
    } else {
        // If the amount is just under max, set it to the extreme
        if (amount > *cam_distance) {
            *cam_distance = max;
        } else {
            // Same but for min
            *cam_distance = min;
        }

    }



}

void toggle_control(bool *user_controlled, SDL_KeyCode keycode) {

    // Any movement key is pressed
    bool move = keycode == SDLK_w||
                keycode == SDLK_a ||
                keycode == SDLK_d ||
                keycode == SDLK_s ||
                keycode == SDLK_UP ||
                keycode == SDLK_DOWN ||
                keycode == SDLK_LEFT ||
                keycode == SDLK_RIGHT;

    // Toggle on C
    if (keycode == SDLK_c) {
        *user_controlled = !*user_controlled;
    }

    // If the user tries to move and the program is not user controlled already
    else if (move && !*user_controlled) {
        // Enter user control
        *user_controlled = true;
    }
}

void move_cube(SDL_KeyCode keycode, float *x_angle, float *y_angle, float speed) {

    // Move up
    if (keycode == SDLK_w || keycode == SDLK_UP) {
        *x_angle += speed;
    }

    // Move down
    if (keycode == SDLK_s || keycode == SDLK_DOWN) {
        *x_angle -= speed;
    }

    // Move left
    if (keycode == SDLK_a || keycode == SDLK_LEFT) {
        *y_angle -= speed;
    }

    // Move right
    if (keycode == SDLK_d || keycode == SDLK_RIGHT) {
        *y_angle += speed;
    }

}