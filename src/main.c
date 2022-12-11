#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "shapes.h"

// Window parameters
const int width = 800;
const int height = 800;
const float fov = 0.785f;
const float aspect_ratio = (float) height / (float) width;
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
    SDL_Event event;

    // Origin
    Vec3D *origin = make_vector(
        (float) width / (2.0f * scale),
        (float) height / (2.0f * scale),
        50.0f
    );
    Matrix *origin_trans = make_translation_matrix(origin, 1);

    // Initialize assets
    float side_length = 40.0f;
    Cube *cube = make_cube(side_length);

    RGB stroke = {255, 255, 255}; // Start as white
    float angle = 0;

    // Projection
    Matrix *proj = make_projection_matrix(fov, aspect_ratio, 0.0f, 100.0f);

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black bg
        SDL_RenderClear(renderer);

        // Draw
        SDL_SetRenderDrawColor(renderer, stroke.r, stroke.g, stroke.b, 255); // Variable stroke
        angle += 0.012f;

        // Reset angle every period
        if (2 * PI - 0.025f < angle & angle > 2 * PI + 0.025f) {
            angle = 0;
        }

        colour_transition(&stroke, angle * 1.0f); // Gives rainbow effect

        // Overwrite cube with rotated cube
        Cube *rotated_cube = rotate_cube(cube, angle, 1); // X axis
        rotated_cube = rotate_cube(rotated_cube, angle, 2); // Y axis

        // Translate to center of screen
        translate_cube(rotated_cube, origin_trans);

        // Project
//        project_cube(rotated_cube, proj);

        // Draw
        draw_cube(renderer, rotated_cube);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
