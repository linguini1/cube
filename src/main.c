#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "shapes.h"
#include "handlers.h"

// Window parameters
const int width = 800;
const int height = 800;
const char window_name[] = "Geometry Visualizer";
const float scale = 3.0f;

int main(int argc, char **argv) {

    // OpenGL params
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        window_name,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Accelerated and in sync with monitor refresh rate
    );
    SDL_RenderSetScale(renderer, scale, scale);

    bool running = true;
    bool perspective = false;
    bool user_controlled = false;
    SDL_Event event;

    // Origin
    float side_len = 100.0f;
    float cam_distance = 1.7f;
    float speed = 0.012f;
    Vec3D *origin = make_vector(
        (float) width / 6,
        (float) height / 6,
        300.0f
    );
    Matrix *origin_trans = make_translation_matrix(origin, (float) side_len);

    // Initialize assets
    Cube *cube = make_cube();
    RGB stroke = {255, 255, 255}; // Start as white
    float c_angle = 0;
    float x_angle = 0;
    float y_angle = 0;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                perspective = !perspective; // Change perspective on click
            } else if (event.type == SDL_MOUSEWHEEL) {
                // Change camera distance
                change_cam_distance(
                    &cam_distance,
                    event.wheel.preciseY,
                    5.0f,
                    1.7f
                );
            } else if (event.type == SDL_KEYDOWN) {

                // Enter user control on C key
                toggle_control(&user_controlled, event.key.keysym.sym);

                // Rotate cube (y left and right, x up and down)
                move_cube(event.key.keysym.sym, &x_angle, &y_angle, 2 * speed);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black bg
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, stroke.r, stroke.g, stroke.b, 255); // Variable stroke

        c_angle += speed;
        if (!user_controlled) {
            x_angle += speed;
            y_angle += speed;
        }

        // Reset angle every period
        reset_angle(&c_angle);
        reset_angle(&x_angle);
        reset_angle(&y_angle);

        // Rainbow effect
        colour_transition(&stroke, c_angle);

        // Create a local rotated cube
        Cube *rotated_cube = rotate_cube(cube, x_angle, 1); // X axis
        rotated_cube = rotate_cube(rotated_cube, y_angle, 2); // Y axis

        // Project
        if (perspective) {
            project_cube(rotated_cube, cam_distance);
        }

        // Translate to center of screen
        translate_cube(rotated_cube, origin_trans);

        // Draw
        draw_cube(renderer, rotated_cube);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free_cube(cube);
    free(origin_trans);

    return 0;
}
