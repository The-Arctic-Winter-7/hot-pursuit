#include <bn_core.h>
#include <bn_display.h>
#include <bn_size.h>
#include <bn_random.h>
#include <bn_timers.h>
#include <bn_log.h>

#include "create_bounding_box.h"
#include "spawn_enemy.h"

#include "ScoreDisplay.h"
#include "Enemy.h"
#include "Player.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr bn::fixed PLAYER_SPEED = 1.5;
static constexpr bn::fixed ENEMY_SPEED = 0.5;

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    Player player = Player(44, 22, PLAYER_SPEED, PLAYER_SIZE, create_bounding_box(player.sprite, player.size));

    // Enemy enemy = Enemy(20, -12, ENEMY_SIZE, create_bounding_box(enemy.sprite, enemy.enemySize), 0.5);
    bn::vector<Enemy, MAX_ENEMIES> enemy = {};
    spawn_enemy(enemy, 20, -12, ENEMY_SIZE, ENEMY_SPEED);

    bn::random rng = bn::random();
    rng.update(); // Forces a new seed every time the game is ran

    int enemy_spawn_counter = 0;

    bool has_collided = false;

    while (true)
    {
        if (enemy_spawn_counter / 60 >= 5)
        {
            enemy_spawn_counter = 0;
            spawn_enemy(enemy, rng.get_unbiased_fixed(MIN_X, MAX_X), rng.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, ENEMY_SPEED);
        }

        player.update();
        for (Enemy &enemies : enemy)
        {
            enemies.update(player);
        }

        // Reset the current score and player position if the player collides with enemy
        for (Enemy &enemies : enemy)
            if (enemies.bounding_box.intersects(player.bounding_box))
                has_collided = true;

        if (has_collided)
        {
            scoreDisplay.resetScore();
            player.sprite.set_x(44);
            player.sprite.set_y(22);
            enemy.clear();
            spawn_enemy(enemy, rng.get_unbiased_fixed(MIN_X, MAX_X), rng.get_unbiased_fixed(MIN_Y, MAX_Y), ENEMY_SIZE, ENEMY_SPEED);
            enemy_spawn_counter = 0;
            has_collided = false;
        }

        // Update the scores and disaply them
        scoreDisplay.update();
        enemy_spawn_counter++;
        bn::core::update();
    }
}