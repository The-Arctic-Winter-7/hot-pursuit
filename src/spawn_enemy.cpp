#include "spawn_enemy.h"

void spawn_enemy(bn::vector<Enemy, MAX_ENEMIES> &enemy, bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed speed)
{
    if (enemy.size() < MAX_ENEMIES)
    {
        Enemy enemy_instance = Enemy(x_start, y_start, size, speed);
        enemy.push_back(enemy_instance);
    }
}