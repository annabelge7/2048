#include "model.hxx"
#include <iostream>


Model::Model():
        score_(0),
        winner_(' ')

{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board_[i][j] = ' ';
        }
    }
    board_[0][0] = '2';
    board_[0][1] = '2';

    //UNCOMMENT THIS TO TEST THAT THE GRAY TILES APPEAR AND THE GAME IS WON
    // WHEN YOU HIT 2048
    //--------------------Uncomment below------------
    // board_[0][2] = 'g';
    // board_[0][3] = 'g';
    //-----------------------------------------------

    // 16 = a
    // 32 = b
    // 64 = c
    // 128 = d
    // 256 = e
    // 512 = f
    // 1024 = g
    // 2048 = h
}

void Model::update_score(char val)
{
    if (val == '2') {
        score_ = score_ + 2;
    }
    if (val == '4') {
        score_ = score_ + 4;
    }
    if (val == '8') {
        score_ += 8;
    }
    if (val == 'a') {
        score_ += 16;
    }
    if (val == 'b') {
        score_ += 32;
    }
    if (val == 'c') {
        score_ += 64;
    }
    if (val == 'd') {
        score_ += 128;
    }
    if (val == 'e') {
        score_ += 256;
    }
    if (val == 'f') {
        score_ += 512;
    }
    if (val == 'g') {
        score_ += 1024;
    }
    if (val == 'h') {
        score_ += 2048;
    }
}

char Model::merge_tiles_and_score(char board1) {
    if (board1 == '2') {
        return '4';
    }
    if (board1 == '4') {
        return '8';
    }
    if (board1 == '8') {
        return 'a';
    }
    if (board1 == 'a') {
        return 'b';
    }
    if (board1 == 'b') {
        return 'c';
    }
    if (board1 == 'c') {
        return 'd';
    }
    if (board1 == 'd') {
        return 'e';
    }
    if (board1 == 'e') {
        return 'f';
    }
    if (board1 == 'f') {
        return 'g';
    }
    if (board1 == 'g') {
        return 'h';
    }
    return '2';
}


bool Model::move_tile(ge211::geometry::Posn<int>cur_posn,
                      ge211::geometry::Posn<int>dir) {
    // Takes a posn with a tile and a direction to move the tile
    bool has_moved = false;
    while (true) {
        ge211::geometry::Posn<int>next_posn = {cur_posn.x + dir.x,
                                               cur_posn.y + dir.y};
        // checks if next position is out of bounds
        if (next_posn.x < 0 ||
            next_posn.x > 3 ||
            next_posn.y < 0 ||
            next_posn.y > 3) {
            break;
        }
        // checks if the next position has a tile that is the same as the
        // current tile
        if (board_[next_posn.x][next_posn.y] != ' ') {
            if (board_[next_posn.x][next_posn.y] == board_[cur_posn
                    .x][cur_posn.y]) {
                char new_val = merge_tiles_and_score(board_[next_posn.x]
                                                     [next_posn.y]);
                board_[next_posn.x][next_posn.y] = new_val;
                update_score(new_val);
                board_[cur_posn.x][cur_posn.y] = ' ';
                has_moved = true;
            }
            break;
        }
        // if the next position is empty then make the next tile the current one
        if (board_[next_posn.x][next_posn.y] == ' ') {
            board_[next_posn.x][next_posn.y] = board_[cur_posn.x][cur_posn.y];
            board_[cur_posn.x][cur_posn.y] = ' ';
            has_moved = true;
        }
        cur_posn = next_posn;
    }
    return has_moved;
}


void Model::move_up() // this function moves all the tiles up
{
    if (key_pressed == ' ') {
        bool tile_moved = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board_[i][j] != ' ') {
                    if (move_tile({i, j}, {0, -1})) {
                        tile_moved = true;
                    }
                }
            }
        }
        if (tile_moved) {
            insert_random_two();
        }
    } else {
        return;
    }
}

void Model::move_down() // this function moves all the tiles down
{
    if (key_pressed == ' ') {
        bool tile_moved = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {
                if (board_[i][j] != ' ') {
                    if (move_tile({i, j}, {0, 1})) {
                        tile_moved = true;
                    }
                }
            }
        }
        if (tile_moved) {
            insert_random_two();
        }
    } else {
        return;
    }
}

void Model::move_right() // this function moves all the tiles to the right
{
    if (key_pressed == ' ') {
        bool tile_moved = false;
        for (int j = 0; j < 4; j++) {
            for (int i = 3; i >= 0; i--) {
                if (board_[i][j] != ' ') {
                    if (move_tile({i, j}, {1, 0})) {
                        tile_moved = true;
                    }
                }
            }
        }
        if (tile_moved) {
            insert_random_two();
        }
    } else {
        return;
    }
}

void Model::move_left() // this function moves all the tiles to the left
{
    if (key_pressed == ' ') {
        bool tile_moved = false;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                if (board_[i][j] != ' ') {
                    if (move_tile({i, j}, {-1, 0})) {
                        tile_moved = true;
                    }
                }
            }
        }
        if (tile_moved) {
            insert_random_two();
        }
    } else {
        return;
    }
}


void Model::game_over() // checks if there are valid moves left if the board
// is full and if the board has no valid moves the game is over
{
    bool any_valid_moves = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j] != ' ') {
                if (valid_moves({i, j}, {0, -1})) {
                    //up
                    any_valid_moves = true;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j] != ' ') {
                if(valid_moves({i, j}, {-1, 0})) {
                    //left
                    any_valid_moves = true;
                }
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 0; i--) {
            if (board_[i][j] != ' ') {
                if (valid_moves({i, j}, {0, 1})) {
                    //down
                    any_valid_moves = true;
                }
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 0; i--) {
            if (board_[i][j] != ' ') {
                if (valid_moves({i, j}, {1, 0})) {
                    //right
                    any_valid_moves = true;
                }
            }
        }
    }
    if (any_valid_moves) {
        return;
    }

    winner_ = 'n';
    set_key('n');
}



void Model::game_won() //checks if 2048 is on the board and if so the game is
// won by the player
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j] == 'h') {
                winner_ = 'u';
                set_key('n');
            }
        }
    }
}

void Model::insert_random_two() // checks for 2048 and if 2048 is not on the
// board inserts a random two tile on the board to keep the game going
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board_[i][j] == 'h') {
                return;
            }
        }
    }
    while (true) {
        int i = rand() % (3 - 0 + 1) + 0;
        int j = rand() % (3 - 0 + 1) + 0;
        if (board_[i][j] == ' ') {
            board_[i][j] = '2';
            break;
        }
    }
}


bool Model::valid_moves(ge211::geometry::Posn<int>cur_posn,
                        ge211::geometry::Posn<int>dir)
{
    bool valid_moves = false;
    while (true) {
        ge211::geometry::Posn<int>next_posn = {cur_posn.x + dir.x,
                                               cur_posn.y + dir.y};
        // checks if next position is out of bounds
        if (next_posn.x < 0 ||
            next_posn.x > 3 ||
            next_posn.y < 0 ||
            next_posn.y > 3) {
            break;
        }
        // checks if the next position has a tile that is the same as the
        // current tile
        if (board_[next_posn.x][next_posn.y] != ' ') {
            if (board_[next_posn.x][next_posn.y] == board_[cur_posn
                    .x][cur_posn.y]) {
                valid_moves = true;
            }
            break;
        }
        // if the next position is empty then valid move
        if (board_[next_posn.x][next_posn.y] == ' ') {
            valid_moves = true;
        }
        cur_posn = next_posn;
    }
    return valid_moves;
}

