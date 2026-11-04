#pragma once

#include <bn_vector.h>
#include "Enemy.h"

void spawn_enemy(bn::vector<Enemy, Enemy::MAX_ENEMIES> &enemy, bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed speed);