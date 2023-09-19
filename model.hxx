#pragma once

#include <ge211.hxx>

class Model
{
public:
    // using Coordinate = Board::Coordinate;
    // using Dimensions = Board::Dimensions;
    // using Position = Board::Position;
    // using Position_set = Board::Position_set;

    Model();
    // Dimensions board_dimensions);

    bool move_tile(ge211::Posn<int>, ge211::Posn<int>);

    void move_up();

    void move_down();

    void move_right();

    void move_left();

    char merge_tiles_and_score(char);

    bool is_game_over() const
    {return winner_ == 'n';}

    bool is_game_won() const
    { return winner_ == 'u'; }

    void game_won();

    void game_over();

    size_t score_;

    char board_[4][4];

    void insert_random_two();

    void update_score(char);

    void set_key(char c) {
        key_pressed = c;
    }

    bool valid_moves(ge211::Posn<int>, ge211::Posn<int>);

private:
    char winner_;

    char key_pressed = ' ';

    std::vector<char>empty_board;

};