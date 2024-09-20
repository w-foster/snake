#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board {

    size_t board_W, board_H;
    std::vector<std::vector<int>> board_state;

    int fruit_row, fruit_col;


    public:
    // Constructor & destructor
    Board(size_t new_board_W, size_t new_board_H);
    ~Board();

    // Getters
    size_t getBoardWidth() const;
    size_t getBoardHeight() const;
    const std::vector<std::vector<int>>& getBoardState() const;
    int getFruitRow() const;
    int getFruitCol() const;

    // Other methods
    void newFruit(const std::vector<std::vector<int>>& snake_body);

};


#endif