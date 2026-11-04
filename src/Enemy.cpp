#include "Enemy.h"
#include "create_bounding_box.h"
#include "bn_sprite_items_velociraptor.h"

Enemy::Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::rect enemy_bounding_box, bn::fixed enemy_speed) : sprite(bn::sprite_items::velociraptor.create_sprite(x_start, y_start)),
                                                                                                                     enemySize(size), bounding_box(enemy_bounding_box),
                                                                                                                     speed(enemy_speed)
{
}

void Enemy::update(Player &player)
    {
        if (sprite.x() < player.sprite.x())
        {
            sprite.set_x(sprite.x() + speed);
        }
        if (sprite.x() > player.sprite.x())
        {
            sprite.set_x(sprite.x() - speed);
        }

        if (sprite.y() < player.sprite.y())
        {
            sprite.set_y(sprite.y() + speed);
        }
        if (sprite.y() > player.sprite.y())
        {
            sprite.set_y(sprite.y() - speed);
        }

        bounding_box = create_bounding_box(sprite, enemySize);
    }