#include "Player.h"

Player::Player(bn::fixed x_start, bn::fixed y_start, bn::fixed playerSpeed, bn::size playerSize, bn::rect playerBoundingBox)
    : sprite(bn::sprite_items::dot.create_sprite(x_start, y_start)), base_speed(playerSpeed),
      size(playerSize), bounding_box(playerBoundingBox)
{
}

void Player::update()
{
    bn::fixed x_component = 0;
    bn::fixed y_component = 0;

    if (bn::keypad::right_held() && sprite.x() <= MAX_X)
        x_component = base_speed;

    if (bn::keypad::left_held() && sprite.x() >= MIN_X)
        x_component = -base_speed;

    if (bn::keypad::up_held() && sprite.y() >= MIN_Y)
        y_component = -base_speed;

    if (bn::keypad::down_held() && sprite.y() <= MAX_Y)
        y_component = base_speed;

    bn::fixed magnitude = bn::sqrt((x_component * x_component) + (y_component * y_component));

    if (magnitude > 0)
    {
        sprite.set_x(sprite.x() + ((x_component / magnitude) * base_speed));
        sprite.set_y(sprite.y() + ((y_component / magnitude) * base_speed));
    }

    bounding_box = create_bounding_box(sprite, size);
}