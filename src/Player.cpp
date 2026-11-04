#include "Player.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Player::Player(bn::fixed x_start, bn::fixed y_start, bn::fixed playerSpeed, bn::size playerSize, bn::rect playerBoundingBox)
    : sprite(bn::sprite_items::dot.create_sprite(x_start, y_start)), base_speed(playerSpeed), speed(bn::vector<bn::fixed, 2>()),
      size(playerSize), bounding_box(playerBoundingBox)
{
}

void Player::update()
{
    if (bn::keypad::right_held())
    {
        if (sprite.x() > MAX_X)
        {
            sprite.set_x(MAX_X - 1);
        }
        // sprite.set_x(sprite.x() + speed);
        speed[0] = base_speed;
    }
    else
        speed[0] = 0;
    if (bn::keypad::left_held())
    {
        if (sprite.x() < MIN_X)
        {
            sprite.set_x(MIN_X + 1);
        }
        // sprite.set_x(sprite.x() - speed);
        speed[0] = -base_speed;
    }
    else
        speed[0] = 0;
    if (bn::keypad::up_held())
    {
        if (sprite.y() < MIN_Y)
        {
            sprite.set_y(MIN_Y + 1);
        }
        // sprite.set_y(sprite.y() - speed);
        speed[1] = -base_speed;
    }
    else
        speed[1] = 0;
    if (bn::keypad::down_held())
    {
        if (sprite.y() > MAX_Y)
        {
            sprite.set_y(MAX_Y - 1);
        }
        // sprite.set_y(sprite.y() + speed);
        speed[1] = base_speed;
    }
    else
        speed[1] = 0;

    if (speed[0] != 0 && speed[1] != 0)
    {
        speed[0] *= bn::sqrt(2) / 2;
        speed[1] *= bn::sqrt(2) / 2;
    }

    sprite.set_x(sprite.x() + speed[0]);
    sprite.set_y(sprite.y() + speed[1]);

    bounding_box = create_bounding_box(sprite, size);
}