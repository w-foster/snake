#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <SDL.h>

#include "board.h"
#include "snake_character.h"

class Renderer {

    SDL_Renderer* renderer;
    SDL_Window* window;
    int width, height;
    int rect_size;
    int space_left, space_above;

    public:
    // Constructor and destructor
    Renderer(int screen_W, int screen_H, int new_rect_size);
    ~Renderer();

    // Core SDL-related methods
    bool sdlInit();
    void renderClear();
    void renderPresent();
    
    // Snake-specific SDL-related methods
    void renderBoard(const Board& board_to_render);
    void renderSnakeCharacter(const SnakeCharacter& snake_to_render);


};








#endif