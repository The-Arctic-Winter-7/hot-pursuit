#include "Enemy.h"

Enemy::Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed enemy_speed) : sprite(bn::sprite_items::velociraptor.create_sprite(x_start, y_start)),
                                                                                           enemySize(size), bounding_box(create_bounding_box(sprite, size)),
                                                                                           speed(enemy_speed), has_collided_top(false), has_collided_bottom(false),
                                                                                           has_collided_left(false), has_collided_right(false)
{
}

void Enemy::update(Player &player)
{
    if (sprite.x() < player.sprite.x() && !has_collided_right)
    {
        sprite.set_x(sprite.x() + speed);
        BN_LOG("Moving right!");
    }
    if (sprite.x() > player.sprite.x() && !has_collided_left)
    {
        sprite.set_x(sprite.x() - speed);
        BN_LOG("Moving left!");
    }

    if (sprite.y() < player.sprite.y() && !has_collided_bottom)
    {
        sprite.set_y(sprite.y() + speed);
        BN_LOG("Moving down!");
    }
    if (sprite.y() > player.sprite.y() && !has_collided_top)
    {
        sprite.set_y(sprite.y() - speed);
        BN_LOG("Moving up!");
    }

    bounding_box = create_bounding_box(sprite, enemySize);
}