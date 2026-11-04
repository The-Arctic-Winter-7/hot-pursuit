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
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"

#include "create_bounding_box.h"

#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

static constexpr int MAX_ENEMIES = 3;

class Player
{
public:
    bn::sprite_ptr sprite;
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision

    Player(bn::fixed x_start, bn::fixed y_start, bn::fixed playerSpeed, bn::size playerSize, bn::rect playerBoundingBox) : sprite(bn::sprite_items::dot.create_sprite(x_start, y_start)),
                                                                                                                           speed(playerSpeed), size(playerSize), bounding_box(playerBoundingBox)
    {
    }
    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update()
    {
        if (bn::keypad::right_held())
        {
            if (sprite.x() > MAX_X)
            {
                sprite.set_x(MAX_X - 1);
            }
            sprite.set_x(sprite.x() + speed);
        }
        if (bn::keypad::left_held())
        {
            if (sprite.x() < MIN_X)
            {
                sprite.set_x(MIN_X + 1);
            }
            sprite.set_x(sprite.x() - speed);
        }
        if (bn::keypad::up_held())
        {
            if (sprite.y() < MIN_Y)
            {
                sprite.set_y(MIN_Y + 1);
            }
            sprite.set_y(sprite.y() - speed);
        }
        if (bn::keypad::down_held())
        {
            if (sprite.y() > MAX_Y)
            {
                sprite.set_y(MAX_Y - 1);
            }
            sprite.set_y(sprite.y() + speed);
        }
        bounding_box = create_bounding_box(sprite, size);
    }
};

class Enemy
{
public:
    bn::sprite_ptr sprite;
    bn::size enemySize;
    bn::rect bounding_box;
    bn::fixed speed;

    Enemy(bn::fixed x_start, bn::fixed y_start, bn::size size, bn::rect enemy_bounding_box, bn::fixed enemy_speed) : sprite(bn::sprite_items::square.create_sprite(x_start, y_start)),
                                                                                                                     enemySize(size), bounding_box(enemy_bounding_box),
                                                                                                                     speed(enemy_speed)
    {
    }

    void update(Player &player)
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
};

void spawn_enemy(bn::vector<Enemy, MAX_ENEMIES> &enemy, bn::fixed x_start, bn::fixed y_start, bn::size size, bn::fixed speed)
{
    Enemy enemy_instance = Enemy(x_start, y_start, ENEMY_SIZE, create_bounding_box(enemy_instance.sprite, enemy_instance.enemySize), speed);
    enemy.push_back(enemy_instance);
}

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