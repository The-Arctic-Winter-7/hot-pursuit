#include "Player.h"
#include "bn_sprites.h"
#include "bn_sprite_items_dot.h"
#include "create_bounding_box.h"
#include <bn_display.h>

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Player::Player(bn::fixed x_start, bn::fixed y_start, bn::fixed playerSpeed, bn::size playerSize, bn::rect playerBoundingBox) : sprite(bn::sprite_items::dot.create_sprite(x_start, y_start)),
                                                                                                                           speed(playerSpeed), size(playerSize), bounding_box(playerBoundingBox)
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
            sprite.set_x(sprite.x() + speed);
        }
        if (bn::keypad::left_held())
        {
            if (sprite.x() < MIN_X)
            {
                sprite.set_x(MIN_X + 1);
            }
            sprite.set_x(sprite.x() - speed);
        }
        if (bn::keypad::up_held())
        {
            if (sprite.y() < MIN_Y)
            {
                sprite.set_y(MIN_Y + 1);
            }
            sprite.set_y(sprite.y() - speed);
        }
        if (bn::keypad::down_held())
        {
            if (sprite.y() > MAX_Y)
            {
                sprite.set_y(MAX_Y - 1);
            }
            sprite.set_y(sprite.y() + speed);
        }
        bounding_box = create_bounding_box(sprite, size);
    }