#include <iostream>
#include <vector>
#include <SDL.h>

#include "renderer.h"

// Constructor and destructor definitions
Renderer::Renderer(int screen_W, int screen_H, int new_rect_size)
    : window(nullptr), renderer(nullptr), width(screen_W), height(screen_H), rect_size(new_rect_size) {}

Renderer::~Renderer() {}

// Core SDL-related method definitions
bool Renderer::sdlInit() {

    // Initialise SDL video
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error with SDL video initialisation: \n" << SDL_GetError() << std::endl;
        return false;
    }

    // Create SDL window
    window = SDL_CreateWindow("Snake Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error with SDL window creation: \n" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_RaiseWindow(window);

    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error with SDL renderer creation: \n" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}



void Renderer::renderClear() {
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, 159, 226, 191, 255);
    SDL_RenderClear(renderer);
}

void Renderer::renderPresent() {
    SDL_RenderPresent(renderer);
}


// Snake-specific SDL-related method definitions
void Renderer::renderBoard(const Board& board_to_render) {

    const std::vector<std::vector<int>>& board_state_to_render = board_to_render.getBoardState();
    size_t board_H = board_to_render.getBoardHeight();
    size_t board_W = board_to_render.getBoardWidth();
    // The -100 at the end is a quick fix for this partially broken centering system
    space_left = ((width - (board_W * rect_size)) / 2) - 100;
    space_above = (height - (board_H * rect_size)) / 2;

    for (int row = 0; row < board_H; row++) {
        for (int col = 0; col < board_W; col++) {

            SDL_Rect rect;
            rect.x = (col * rect_size) + space_left;
            rect.y = (row * rect_size) + space_above;
            rect.w = rect_size;
            rect.h = rect_size;
            
            // Check if cell is filled by a fruit, or not (empty)
            if (board_state_to_render[row][col] < 0) {
                //SDL_SetRenderDrawColor(renderer, 21, 212, 46, 255);
                SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
            } else {
                //SDL_SetRenderDrawColor(renderer, 110, 39, 4, 255);
                SDL_SetRenderDrawColor(renderer, 152, 255, 152, 255);
            }
            // Render the rectangle
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Render board borders
    SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
    int thickness = 4;
    for (int line = 0; line < thickness; line++) {
        // Top line, then bottom line
        SDL_RenderDrawLine(renderer, space_left, space_above - line - 1, space_left + board_W * rect_size - 1, space_above - line - 1);
        SDL_RenderDrawLine(renderer, space_left, space_above + line + board_H * rect_size, space_left + board_W * rect_size - 1, space_above + line + board_H * rect_size);
        // Left line, then right line
        SDL_RenderDrawLine(renderer, space_left - line - 1, space_above - thickness + 1 - 1, space_left - line - 1, space_above + thickness - 1 + board_H * rect_size);
        SDL_RenderDrawLine(renderer, space_left + board_W * rect_size + line, space_above - thickness + 1 - 1, space_left + board_W * rect_size + line, space_above + thickness - 1 + board_H * rect_size);

    }
    

}

void Renderer::renderSnakeCharacter(const SnakeCharacter& snake_to_render) {

    auto snake_body_to_render = snake_to_render.getSnakeBody();
    int num_of_pieces = snake_to_render.getSnakeSize();
    for (int piece_idx = 0; piece_idx < num_of_pieces; piece_idx++) {

        int piece_col = snake_body_to_render[piece_idx][0];
        int piece_row = snake_body_to_render[piece_idx][1];

        SDL_Rect rect;
        rect.x = (piece_col * rect_size) + space_left;
        rect.y = (piece_row * rect_size) + space_above;
        rect.w = rect_size;
        rect.h = rect_size;

        // Draw filled rect
        //SDL_SetRenderDrawColor(renderer, 209, 107, 160, 255);
        SDL_SetRenderDrawColor(renderer, 157, 193, 131, 255);
        SDL_RenderFillRect(renderer, &rect);
        // Draw rect outline/border
        //SDL_SetRenderDrawColor(renderer, 156, 74, 116, 255);
        SDL_SetRenderDrawColor(renderer, 152, 255, 152, 255);
        SDL_RenderDrawRect(renderer, &rect);


    }

}


