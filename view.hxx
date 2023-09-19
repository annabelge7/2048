#pragma once

#include "model.hxx"

class View
{
public:

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    ge211::Font sans35{"sans.ttf", 35};
    ge211::Font sans40{"sans.ttf", 40};
    ge211::Font sans50{"sans.ttf", 50};
    ge211::Font sans72{"sans.ttf", 72};


private:
    Model const& model_;
    ge211::Rectangle_sprite const grid_sprite;
    ge211::Rectangle_sprite const loser_grey_sprite;
    ge211::Rectangle_sprite const two_tile;
    ge211::Rectangle_sprite const four_tile;
    ge211::Rectangle_sprite const eight_tile;
    ge211::Rectangle_sprite const sixteen_tile;
    ge211::Rectangle_sprite const thirtytwo_tile;
    ge211::Rectangle_sprite const sixtyfour_tile;
    ge211::Rectangle_sprite const onetwentyeight_tile;
    ge211::Rectangle_sprite const twofiftysix_tile;
    ge211::Rectangle_sprite const fivetwelve_tile;
    ge211::Rectangle_sprite const thousandtwentyfour_tile;
    ge211::Rectangle_sprite const twentyfortyeight_tile;
    ge211::Text_sprite const two_num;
    ge211::Text_sprite const four_num;
    ge211::Text_sprite const eight_num;
    ge211::Text_sprite const sixteen_num;
    ge211::Text_sprite const thirtytwo_num;
    ge211::Text_sprite const sixtyfour_num;
    ge211::Text_sprite const onetwentyeight_num;
    ge211::Text_sprite const twofiftysix_num;
    ge211::Text_sprite const fivetwelve_num;
    ge211::Text_sprite const thousandtwentyfour_num;
    ge211::Text_sprite const twentyfortyeight_num;
    ge211::Text_sprite const loser_text_sprite;
    ge211::Text_sprite const winner_text_sprite;
    ge211::Text_sprite score_sprite_;
    std::size_t previous_score_;

    void draw_score_(ge211::Sprite_set&);

};
