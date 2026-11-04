#pragma once

#include <bn_vector.h>
#include "Enemy.h"


static constexpr int MAX_ENEMIES = 3;

void spawn_enemy(bn::vector<Enemy, MAX_ENEMIES> &enemy, bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed speed);