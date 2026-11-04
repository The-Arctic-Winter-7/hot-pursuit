#include "check_enemy_collision.h"

void check_enemy_collision(bn::vector<Enemy, Enemy::MAX_ENEMIES> &enemies)
{
    if (enemies.size() >= 2)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            for (int j = i + 1; j < enemies.size(); j++)
            {
                if (enemies[i].bounding_box.intersects(enemies[j].bounding_box))
                {
                    if (enemies[i].sprite.x() < enemies[j].sprite.x())
                    {
                        enemies[i].has_collided_right = true;
                        enemies[j].has_collided_left = true;
                    }
                    if (enemies[i].sprite.x() > enemies[j].sprite.x())
                    {
                        enemies[i].has_collided_left = true;
                        enemies[j].has_collided_right = true;
                    }
                    if (enemies[i].sprite.y() < enemies[j].sprite.y())
                    {
                        enemies[i].has_collided_bottom = true;
                        enemies[j].has_collided_top = true;
                    }
                    if (enemies[i].sprite.y() > enemies[j].sprite.y())
                    {
                        enemies[i].has_collided_top = true;
                        enemies[j].has_collided_bottom = true;
                    }
                }
                else
                {
                    enemies[i].has_collided_right = false;
                    enemies[i].has_collided_left = false;
                    enemies[i].has_collided_bottom = false;
                    enemies[i].has_collided_top = false;

                    enemies[j].has_collided_right = false;
                    enemies[j].has_collided_left = false;
                    enemies[j].has_collided_bottom = false;
                    enemies[j].has_collided_top = false;
                }
            }
        }
    }
}