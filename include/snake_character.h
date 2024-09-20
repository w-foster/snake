#ifndef SNAKE_CHARACTER_H
#define SNAKE_CHARACTER_H

#include <iostream>
#include <vector>


class SnakeCharacter {
    
    std::vector<std::vector<int>> snake_body;
    // 0: right, 1: down, 2: left, 3: up
    int current_direction;
    bool pending_direction_change;
    size_t board_H;
    size_t board_W;
    int fruit_strength;
    int pieces_to_grow;
    
    public:
    SnakeCharacter(int snake_starting_size, size_t new_board_H, size_t new_board_W, int new_fruit_strength);
    ~SnakeCharacter();

    // Getters
    const std::vector<std::vector<int>>& getSnakeBody() const;
    std::vector<int> getSnakeHead() const;
    std::vector<int> getSnakeTail() const;
    int getSnakeSize() const;

    // Other methods
    bool tryChangeSnakeDirection(int new_direction);
    bool tryMoveSnake();
    bool checkFruitCollision(int fruit_col, int fruit_row);
    void growSnake(std::vector<int> old_tail_coords);

};



#endif