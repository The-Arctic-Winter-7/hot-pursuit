#pragma once

#include <bn_sprite_ptr.h>
#include <bn_sprites_actions.h>
#include <bn_log.h>

#include "Player.h"
#include "create_bounding_box.h"
#include "bn_sprite_items_velociraptor.h"

class Enemy
{
public:
    static constexpr int MAX_ENEMIES = 3;
    
    bn::sprite_ptr sprite;
    bn::size enemySize;
    bn::rect bounding_box;
    bn::fixed base_speed;

    bool has_collided_top;
    bool has_collided_bottom;
    bool has_collided_left;
    bool has_collided_right;

    Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed enemy_speed);

    void update(Player &player);
};