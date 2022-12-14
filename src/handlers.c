// Handles SDL events
#include "handlers.h"
#include <stdio.h>

#define TOLERANCE 0.05

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
