
#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);

}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key(ge211::Key key)
{

    if (key == ge211::Key::up()) {
        model_.move_up();
    }
    //
    if (key == ge211::Key::down()) {
        model_.move_down();
        // model_.set_key(ge211::Key::down());
    }
    //
    if (key == ge211::Key::right()) {
        model_.move_right();
    }

    if (key == ge211::Key::left()){
        model_.move_left();
    }

    model_.game_won();
    model_.game_over();
}
