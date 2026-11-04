#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_random.h>

#include "common_fixed_8x16_font.h"

#include "create_bounding_box.h"
#include "spawn_enemy.h"

#include "ScoreDisplay.h"
#include "Enemy.h"
#include "Player.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

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
    Player player = Player(44, 22, 1.5, PLAYER_SIZE, create_bounding_box(player.sprite, player.size));
    // Enemy enemy = Enemy(20, -12, ENEMY_SIZE, create_bounding_box(enemy.sprite, enemy.enemySize), 0.5);
    bn::vector<Enemy, MAX_ENEMIES> enemy = {};
    spawn_enemy(enemy, 20, -12, ENEMY_SIZE, 0.5);

    bn::random rng = bn::random();
    rng.update();

    while (true)
    {
        player.update();
        enemy[0].update(player);

        // Reset the current score and player position if the player collides with enemy
        if (enemy[0].bounding_box.intersects(player.bounding_box))
        {
            scoreDisplay.resetScore();
            player.sprite.set_x(44);
            player.sprite.set_y(22);
            enemy[0].sprite.set_x(rng.get_unbiased_fixed(MIN_X, MAX_X));
            enemy[0].sprite.set_y(rng.get_unbiased_fixed(MIN_Y, MAX_Y));
        }

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}