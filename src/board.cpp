#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "board.h"

// Constructor and destructor definitions
Board::Board(size_t new_board_W, size_t new_board_H)
    : board_H(new_board_W), board_W(new_board_H), board_state(new_board_W, std::vector<int>(new_board_H, 0)) {

        srand(time(NULL));
        fruit_row = rand() % board_H;
        fruit_col = rand() % board_W;
        // Add the fruit (make the cell have a value of -1)
        board_state[fruit_row][fruit_col] = -1;

    }

Board::~Board() {}

// Getter definitions
size_t Board::getBoardWidth() const {return board_W;}
size_t Board::getBoardHeight() const {return board_H;}
const std::vector<std::vector<int>>& Board::getBoardState() const {return board_state;}
int Board::getFruitRow() const {return fruit_row;}
int Board::getFruitCol() const {return fruit_col;}

// Other method definitions
void Board::newFruit(const std::vector<std::vector<int>>& snake_body) {

    // Remove current (stale/eaten) fruit
    board_state[fruit_row][fruit_col] = 0;
    // Store eaten fruit coords, for later validity checks
    int old_fruit_col = fruit_col;
    int old_fruit_row = fruit_row;

    // Produce new random fruit coords until valid result (i.e., not touching the snake_body)
    bool valid = false;
    while (!valid) {
        // Get new, randomised fruit coords
        fruit_row = rand() % board_H;
        fruit_col = rand() % board_W;
        
        valid = true; // Assume that the coords are valid, for potential counterexample
        // Check if new fruit coords overlap with snake body
        for (int piece_idx = 0; piece_idx < snake_body.size(); piece_idx++) {
            if (std::vector<int> {fruit_col, fruit_row} == snake_body[piece_idx]) {
                valid = false;
            }
        }
        // Check if new fruit coords are too near to old fruit
        if ((abs(old_fruit_col - fruit_col) < (1 + board_W / 4)) || (abs(old_fruit_row - fruit_row) < (1 + board_H / 4))) {
            valid = false;
        }

    }
    
    // Add new, valid fruit to board
    board_state[fruit_row][fruit_col] = -1;

}



