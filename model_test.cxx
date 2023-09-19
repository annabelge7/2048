#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

TEST_CASE("tiles_merging"){ //favorite test #1
    //showing that two tiles will merge if they hit
    //up and right
    //hard to do more because we cannot predict
    //where the random 2 will go
    //checking score
    Model model;

    model.board_[0][0] = '8';
    model.board_[0][1] = '8';
    model.board_[0][2] = '4';
    model.board_[0][3] = '4';

    model.board_[1][0] = '2';
    model.board_[2][0] = '2';
    model.board_[3][0] = '8';

    model.move_up(); //tiles merge right
    CHECK(model.board_[0][0] == 'a'); //a = 16
    CHECK(model.board_[0][1] == '8');
    CHECK(model.score_ == 24);

    model.move_right();
    CHECK(model.board_[2][0] == '4');
    CHECK(model.score_ == 28);

}

TEST_CASE("tiles_merging2"){ //favorite test #2
    //showing that two tiles will merge if they hit
    //down and left
    //hard to do more because we cannot predict
    //where the random 2 will go
    //checking score
    Model model;

    model.board_[0][0] = '8';
    model.board_[0][1] = '8';
    model.board_[0][2] = 'a';
    model.board_[0][3] = 'a';

    model.board_[1][0] = '2';
    model.board_[2][0] = '2';
    model.board_[3][0] = '8';

    model.move_down(); //tiles merge down
    CHECK(model.board_[0][2] == 'a'); //a = 16
    CHECK(model.board_[0][3] == 'b');
    CHECK(model.score_ == 48);

    model.move_left(); //tiles merge left
    CHECK(model.board_[1][3] == '4');
    CHECK(model.score_ == 52);

}

TEST_CASE("2048=game_over"){ //favorite test #3
    //When the player combines to tiles of 1024 (in this case board[0][0] and
    // board[0][1], it creates the tile 2048 and the game is now won by the
    // player.
    Model model;

    model.board_[0][0] = 'g';
    model.board_[0][1] = 'g';
    model.board_[0][2] = '4';
    model.board_[0][3] = '4';

    model.move_up();
    CHECK(model.board_[0][0] == 'h');
    CHECK(model.score_ == 2056);
    model.game_won(); //this is usually done in the controller but cannot be
    // checked here -- this changes is_game_won to true when there is a 2048
    // on the board
    CHECK(model.is_game_won() == true);
}

TEST_CASE("tiles_merging3"){ //favorite test #4
    //This test demonstrates how our game is slightly different from 2048 --
    // as the numbers get higher, because we are only adding twos -- we
    // decided the player would get more of a chance to merge higher numbers.
    // So when four tiles are in a row (ex. 8, 8, 16, 32) instead of just
    // merging the 8 and 8, the 8 and 8 will merge to 16, the two 16s will
    // merge, and the two 32s will merge, leaving the player with a 64
    Model model;

    model.board_[0][0] = '8';
    model.board_[0][1] = '8';
    model.board_[0][2] = 'a'; //a = 16
    model.board_[0][3] = 'b'; //b = 32

    model.board_[1][0] = '2';
    model.board_[2][0] = '2';
    model.board_[3][0] = '8';

    model.move_up(); //tiles merge up
    CHECK(model.board_[0][0] == 'c'); //c = 64
    CHECK(model.score_ == 112);

}

TEST_CASE("check random 2") //favorite test #5
//checks that a random two was added to the board
{
    Model m;
    m.board_[0][0] = '2';
    m.board_[0][1] = '2';
    m.board_[0][2] = '8';
    m.board_[1][0] = 'b';
    m.board_[1][2] = 'c';
    m.board_[1][4] = 'e';
    m.board_[2][0] = 'f';
    m.board_[2][1] = 'g';
    m.board_[2][2] = 'a';
    m.board_[3][0] = 'c';
    m.board_[3][1] = 'd';
    m.board_[3][2] = 'e';
    bool random_two = false;
    m.move_up();
    if (m.board_[0][2] == '2' ||
        m.board_[0][3] == '2' ||
        m.board_[1][2] == '2' ||
        m.board_[1][3] == '2' ||
        m.board_[2][3] == '2' ||
        m.board_[3][3] == '2') {
        random_two = true;
    }
    CHECK(random_two);

}

TEST_CASE("no_more_moves"){
    //this test case demonstrates that when there are no more moves available
    // (aka you can't merge any more tiles) the game will be over
    Model model;

    model.board_[0][0] = '2';
    model.board_[0][1] = '4';
    model.board_[0][2] = 'a';
    model.board_[0][3] = '2';

    model.board_[1][0] = 'c';
    model.board_[1][1] = 'd';
    model.board_[1][2] = 'e';
    model.board_[1][3] = '4';

    model.board_[2][0] = 'g';
    model.board_[2][1] = '4';
    model.board_[2][2] = 'a';
    model.board_[2][3] = 'b';

    model.board_[3][0] = 'c';
    model.board_[3][1] = 'd';
    model.board_[3][2] = 'e';

    model.move_down();
    CHECK(model.board_[3][0] == '2'); //adds a random two in the only spot
    // available
    CHECK(model.score_ == 0);
    model.game_over(); //this is usually done in the controller but cannot be
    // checked here
    CHECK(model.is_game_over() == true);
}
