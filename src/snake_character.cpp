#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "snake_character.h"

// Constructor and destructor definitions
SnakeCharacter::SnakeCharacter(int snake_spawn_size, size_t new_board_H, size_t new_board_W, int new_fruit_strength) 
    : current_direction(0), pending_direction_change(false), board_H(new_board_H), board_W(new_board_W), fruit_strength(new_fruit_strength), pieces_to_grow(0) {

    // Add coords, starting at 0,0
    for (int piece = 0; piece < snake_spawn_size; piece++) {
        snake_body.push_back(std::vector<int> {piece, 0});
    }
    // Then reverse the arrary. We do this because it will end up with the first
    // item being {0,0}, but that is the head, and we dont want the head to be in corner
    std::reverse(snake_body.begin(), snake_body.end());

}

SnakeCharacter::~SnakeCharacter() {}


// Getter definitions
const std::vector<std::vector<int>>& SnakeCharacter::getSnakeBody() const {
    return snake_body;
}

std::vector<int> SnakeCharacter::getSnakeHead() const {
    return snake_body[0];
}

std::vector<int> SnakeCharacter::getSnakeTail() const {
    return snake_body[snake_body.size() - 1];
}

int SnakeCharacter::getSnakeSize() const { 
    return snake_body.size(); 
}


// Other method definitions
bool SnakeCharacter::tryChangeSnakeDirection(int new_direction) {

    // Check if a direction change is already pending 
    // (i.e., we haven't yet gone onto the next 'move' cycle for the change to go through)
    if (pending_direction_change) {
        return false;
    }
    pending_direction_change = true;
    /*
    0 2 --> not allowed to switch between these directions (right and left)
    1 3 --> " " (down and up)
    We can check this by seeing if |current_direction - new_direction| == 2
    We can do that by using the abs() function from cmath
    */

    if (abs(current_direction - new_direction) == 2) {
        return false;
    } else {
        current_direction = new_direction;
        return true;
    }
}

bool SnakeCharacter::tryMoveSnake() {
    
    // Current tail coords (which will BECOME old/stale after movement) to potentially be passed to the growSnake method:
    std::vector<int> old_tail_coord = snake_body[snake_body.size() - 1];

    std::vector<int> current_head_coord = snake_body[0];
    int potential_head_col = current_head_coord[0];
    int potential_head_row = current_head_coord[1];
    switch (current_direction) {
        // Right
        case 0:
            potential_head_col += 1;
            break;
        // Down
        case 1:
            potential_head_row += 1;
            break;
        // Left
        case 2:
            potential_head_col -= 1;
            break;
        // Up
        case 3:
            potential_head_row -= 1;
            break;
        // Default
        default:
            break;
    }
    std::vector<int> potential_head_coord = {potential_head_col, potential_head_row};
    
    // Edge-collision check
    if ((potential_head_coord[0] < 0 || potential_head_coord[0] > board_W - 1) || (potential_head_coord[1] < 0 || potential_head_coord[1] > board_H - 1)) {
        return false;
    }

    // Self-collision check
    int snake_size = getSnakeSize();
    for (int piece_idx = 0; piece_idx < snake_size; piece_idx++) {
        if (potential_head_coord == snake_body[piece_idx]) {
            return false;
        }
    }

    // Move piece
    /*  Rows:
        current: 3, 4, 5, 6
        desired: 2, 3, 4, 5 (move left)
        Start at end (size-1)
        6 becomes 5; 5 becomes 4; ...2 becomes 2
        Stops there. Then coord at index 0 is manually updated to be the new potential head coord.
    */
    for (int piece_idx = snake_size - 1; piece_idx > 0; piece_idx--) {
        snake_body[piece_idx] = snake_body[piece_idx - 1];
    }
    snake_body[0] = potential_head_coord;

    
    // If there are pieces to grow, add them on:
    if (pieces_to_grow > 0) {
        growSnake(old_tail_coord);
    }

    
    pending_direction_change = false;
    return true;
}

bool SnakeCharacter::checkFruitCollision(int fruit_col, int fruit_row) {
    if (getSnakeHead() == std::vector<int> {fruit_col, fruit_row}) {
        pieces_to_grow = fruit_strength;
        return true;
    } else {
        return false;
    }
}

void SnakeCharacter::growSnake(std::vector<int> old_tail_coords) {
    snake_body.push_back(old_tail_coords);
    pieces_to_grow--;

}

