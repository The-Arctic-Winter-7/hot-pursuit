#include "check_enemy_collision.h"

void check_enemy_collision(bn::vector<Enemy, Enemy::MAX_ENEMIES> &enemies)
{
    for (Enemy enemy : enemies)
    {
        enemy.has_collided_bottom = false;
        enemy.has_collided_top = false;
        enemy.has_collided_left = false;
        enemy.has_collided_right = false;
    }
    if (enemies.size() >= 2)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            for (int j = i + 1; j < enemies.size(); j++)
            {
                if (enemies[i].bounding_box.intersects(enemies[j].bounding_box))
                {
                    if (enemies[i].bounding_box.right() >= enemies[j].bounding_box.left())
                    {
                        enemies[i].sprite.set_x(enemies[i].sprite.x() - 1);
                        enemies[j].sprite.set_x(enemies[j].sprite.x() + 1);
                    }
                    if (enemies[i].bounding_box.left() <= enemies[j].bounding_box.right())
                    {
                        enemies[i].sprite.set_x(enemies[i].sprite.x() + 1);
                        enemies[j].sprite.set_x(enemies[j].sprite.x() - 1);
                    }
                    if (enemies[i].bounding_box.bottom() <= enemies[j].bounding_box.top())
                    {
                        enemies[i].sprite.set_y(enemies[i].sprite.y() - 1);
                        enemies[j].sprite.set_y(enemies[j].sprite.y() + 1);
                    }
                    if (enemies[i].bounding_box.top() >= enemies[j].bounding_box.bottom())
                    {
                        enemies[i].sprite.set_y(enemies[i].sprite.y() + 1);
                        enemies[j].sprite.set_y(enemies[j].sprite.y() - 1);
                    }
                }
            }
        }
    }
}