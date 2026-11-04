#pragma once

#include <bn_sprite_ptr.h>
#include <bn_log.h>

#include "Player.h"
#include "create_bounding_box.h"
#include "bn_sprite_items_velociraptor.h"


class Enemy
{
public:
    bn::sprite_ptr sprite;
    bn::size enemySize;
    bn::rect bounding_box;
    bn::fixed speed;

    Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed enemy_speed);

    void update(Player &player);
};