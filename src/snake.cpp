#include <iostream>
#include <SDL.h>
#include <chrono>


#include "snake_character.h"
#include "board.h"
#include "renderer.h"

int main() {

    Renderer renderer_obj(1920, 1090, 35);
    renderer_obj.sdlInit();

    Board board(15, 20);
    SnakeCharacter snake_character(4, board.getBoardHeight(), board.getBoardWidth(), 2);

    bool quit = false;
    SDL_Event event;
    bool needs_rendering = true;
    // Measured in milliseconds:
    const int move_delay = 500;
    auto last_move_time = std::chrono::steady_clock::now();
    // Entering main game loop
    while (!quit) {

        // SDL event polling loop
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
                    snake_character.tryChangeSnakeDirection(3);
                }
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT) {
                    snake_character.tryChangeSnakeDirection(2);
                }
                if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
                    snake_character.tryChangeSnakeDirection(1);
                }
                if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) {
                    snake_character.tryChangeSnakeDirection(0);
                }
            }
        } // end of SDL event polling loop

        // Time checking
        auto current_time = std::chrono::steady_clock::now();
        auto time_since_last_move = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_move_time).count();
        if (time_since_last_move > move_delay) {
            if (snake_character.tryMoveSnake()) {
                last_move_time = current_time;
                needs_rendering = true;
                int f_col = board.getFruitCol();
                int f_row = board.getFruitRow();

                if (snake_character.checkFruitCollision(f_col, f_row)) {
                    board.newFruit(snake_character.getSnakeBody());
                }

            } else {
                SDL_Delay(2000);
                quit = true;
            }
        } // end of time checking

        if (needs_rendering) {
            renderer_obj.renderClear();
            renderer_obj.renderBoard(board);
            renderer_obj.renderSnakeCharacter(snake_character);
            renderer_obj.renderPresent();
        }


    } // end of main game loop

    return 0;
}






