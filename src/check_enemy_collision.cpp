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
                    bn::fixed x_overlap = bn::min(enemies[i].bounding_box.right(), enemies[j].bounding_box.right()) -
                                          bn::max(enemies[i].bounding_box.left(), enemies[j].bounding_box.left());
                    bn::fixed y_overlap = bn::min(enemies[i].bounding_box.bottom(), enemies[j].bounding_box.bottom()) -
                                          bn::max(enemies[i].bounding_box.top(), enemies[j].bounding_box.top());

                    if (x_overlap > 0 && y_overlap > 0)
                    {
                        if (x_overlap >= y_overlap)
                        {
                            if (enemies[i].sprite.x() < enemies[j].sprite.x())
                            {
                                enemies[i].sprite.set_x(enemies[i].sprite.x() - (x_overlap / 2));
                                enemies[j].sprite.set_x(enemies[j].sprite.x() + (x_overlap / 2));
                            }
                            else
                            {
                                enemies[i].sprite.set_x(enemies[i].sprite.x() + (x_overlap / 2));
                                enemies[j].sprite.set_x(enemies[j].sprite.x() - (x_overlap / 2));
                            }
                        }
                        else
                        {
                            if (enemies[i].sprite.y() < enemies[j].sprite.y())
                            {
                                enemies[i].sprite.set_y(enemies[i].sprite.y() - (y_overlap / 2));
                                enemies[j].sprite.set_y(enemies[j].sprite.y() + (y_overlap / 2));
                            }
                            else
                            {
                                enemies[i].sprite.set_y(enemies[i].sprite.y() + (y_overlap / 2));
                                enemies[j].sprite.set_y(enemies[j].sprite.y() - (y_overlap / 2));
                            }
                        }
                    }
                }
                enemies[i].bounding_box = create_bounding_box(enemies[i].sprite, enemies[i].enemySize);
                enemies[j].bounding_box = create_bounding_box(enemies[j].sprite, enemies[j].enemySize);
            }
        }
    }
}