#pragma once

#include "Player.h"

class Enemy
{
public:
    bn::sprite_ptr sprite;
    bn::size enemySize;
    bn::rect bounding_box;
    bn::fixed speed;

    Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::rect enemy_bounding_box, bn::fixed enemy_speed);

    void update(Player &player);
};