#pragma once

#include <bn_vector.h>

#include "Enemy.h"

void check_enemy_collision(bn::vector<Enemy, Enemy::MAX_ENEMIES> &enemies);