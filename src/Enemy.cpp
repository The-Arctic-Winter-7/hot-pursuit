#include "Enemy.h"

Enemy::Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed enemy_speed)
    : sprite(bn::sprite_items::velociraptor.create_sprite(x_start, y_start)), enemySize(size),
      bounding_box(create_bounding_box(sprite, size)), base_speed(enemy_speed),
      has_collided_top(false), has_collided_bottom(false),
      has_collided_left(false), has_collided_right(false)
{
}

void Enemy::update(Player &player)
{
    bn::fixed x_component = 0; // x component of movement vector
    bn::fixed y_component = 0; // y component of movement vector

    if (sprite.x() < player.sprite.x() && !has_collided_right)
        x_component = base_speed;

    if (sprite.x() > player.sprite.x() && !has_collided_left)
        x_component = -base_speed;

    if (sprite.y() < player.sprite.y() && !has_collided_bottom)
        y_component = base_speed;

    if (sprite.y() > player.sprite.y() && !has_collided_top)
        y_component = -base_speed;

    // Magnitude of movement vector
    bn::fixed magnitude = bn::sqrt((x_component * x_component) + (y_component * y_component));

    if (magnitude > 0)
    {
        // As long as the magnitude is not zero, uses vector math to normalize speed
        // in all directions using unit vectors
        sprite.set_x(sprite.x() + ((x_component / magnitude) * base_speed));
        sprite.set_y(sprite.y() + ((y_component / magnitude) * base_speed));
    }

    bounding_box = create_bounding_box(sprite, enemySize);
}