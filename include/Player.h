#pragma once

#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_keypad.h>
#include <bn_rect.h>
class Player
{
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision

    Player(bn::fixed x_start, bn::fixed y_start, bn::fixed playerSpeed, bn::size playerSize, bn::rect playerBoundingBox);
    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update();
};