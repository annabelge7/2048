
#include "view.hxx"

ge211::Color const selection_color {180, 200, 190};

const int grid_size = 100;

View::View(Model const& model)
        : model_(model),
          grid_sprite({grid_size-4,grid_size-4}, {255,255,255}),
          loser_grey_sprite({grid_size-4, grid_size-4}, {222, 222, 222}),
          two_tile({grid_size-4,grid_size-4}, {238,228,218}),
          four_tile({grid_size-4,grid_size-4}, {237,224,200}),
          eight_tile({grid_size-4,grid_size-4}, {242,177,121}),
          sixteen_tile({grid_size-4,grid_size-4}, {245,149,99}),
          thirtytwo_tile({grid_size-4,grid_size-4}, {246,124,95}),
          sixtyfour_tile({grid_size-4,grid_size-4}, {246,94,59}),
          onetwentyeight_tile({grid_size-4,grid_size-4}, {237,207,114}),
          twofiftysix_tile({grid_size-4,grid_size-4}, {237,204,97}),
          fivetwelve_tile({grid_size-4,grid_size-4}, {237,200,80}),
          thousandtwentyfour_tile({grid_size-4,grid_size-4}, {237,197,63}),
          twentyfortyeight_tile({grid_size-4,grid_size-4}, {237,194,46}),
          two_num({"2", sans50}),
          four_num({"4", sans50}),
          eight_num({"8", sans50}),
          sixteen_num({"16", sans50}),
          thirtytwo_num({"32", sans50}),
          sixtyfour_num({"64", sans50}),
          onetwentyeight_num({"128", sans40}),
          twofiftysix_num({"256", sans40}),
          fivetwelve_num({"512", sans40}),
          thousandtwentyfour_num({"1024", sans35}),
          twentyfortyeight_num({"2048", sans35}),
          loser_text_sprite("GAME OVER", sans35),
          winner_text_sprite("GAME WON", sans35),
          score_sprite_("0", sans35)

{ }

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * Dimensions{4, 5};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "2048";
}

void
View::draw(ge211::Sprite_set& set)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            set.add_sprite(grid_sprite, {i * grid_size,
                                         j * grid_size}, 0);

            if (model_.board_[i][j] == '2') {
                set.add_sprite(two_tile, {i * grid_size,
                                          j * grid_size}, 1);
                set.add_sprite(two_num,
                               {i * grid_size + 35,
                                j * grid_size + 1},3);
            }
            if (model_.board_[i][j] == '4') {
                set.add_sprite(four_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(four_num,
                               {i * grid_size + 35,
                                j * grid_size + 1},3);
            }
            if (model_.board_[i][j] == '8') {
                set.add_sprite(eight_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(eight_num,
                               {i * grid_size + 35,
                                j * grid_size + 1},3);
            }
            if (model_.board_[i][j] == 'a') {
                set.add_sprite(sixteen_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(sixteen_num, {i * grid_size + 20,
                                             j * grid_size + 3}, 3);
            }
            if (model_.board_[i][j] == 'b') {
                set.add_sprite(thirtytwo_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(thirtytwo_num, {i * grid_size + 20,
                                               j * grid_size + 3}, 3);
            }
            if (model_.board_[i][j] == 'c') {
                set.add_sprite(sixtyfour_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(sixtyfour_num, {i * grid_size + 20,
                                               j * grid_size + 3}, 3);
            }
            if (model_.board_[i][j] == 'd') {
                set.add_sprite(onetwentyeight_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(onetwentyeight_num,
                               {i * grid_size + 14, j *
                                                    grid_size + 11},
                               3);
            }
            if (model_.board_[i][j] == 'e') {
                set.add_sprite(twofiftysix_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(twofiftysix_num,
                               {i * grid_size + 14, j *
                                                    grid_size + 11},
                               3);
            }
            if (model_.board_[i][j] == 'f') {
                set.add_sprite(fivetwelve_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(fivetwelve_num, {i * grid_size + 14,
                                                j * grid_size + 11}, 3);
            }
            if (model_.board_[i][j] == 'g') {
                set.add_sprite(thousandtwentyfour_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(thousandtwentyfour_num,
                               {i * grid_size + 10, j *
                                                    grid_size + 15},
                               3);
            }
            if (model_.board_[i][j] == 'h') {
                set.add_sprite(twentyfortyeight_tile,
                               {i * grid_size, j * grid_size},
                               1);
                set.add_sprite(twentyfortyeight_num,
                               {i * grid_size + 10, j *
                                                    grid_size + 15},
                               3);
            }
        }
    }

    if (model_.is_game_won()) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                set.add_sprite(loser_grey_sprite, {i * grid_size,
                                                   j * grid_size}, 2);
                set.add_sprite(winner_text_sprite, {180, 430});
                draw_score_(set);
            }
        }
    } else if (model_.is_game_over()) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                set.add_sprite(loser_grey_sprite, {i * grid_size,
                                                   j * grid_size}, 2);
                set.add_sprite(loser_text_sprite, {180, 430});
                draw_score_(set);
            }
        }
    } else {
        draw_score_(set);
    }

}

void
View::draw_score_(ge211::Sprite_set& sprites)
{
    // If the score has changed, update the score sprite.
    if (model_.score_ != previous_score_) {
        ge211::Text_sprite::Builder builder(sans35);
        builder << model_.score_;
        score_sprite_.reconfigure(builder);
    }

    sprites.add_sprite(score_sprite_, {20, 430}, 10);
}







