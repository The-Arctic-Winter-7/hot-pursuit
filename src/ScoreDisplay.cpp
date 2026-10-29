
#include <bn_sprite_text_generator.h>
#include <bn_sprite_text_generator.h>

#include "common_fixed_8x16_font.h"

#include "ScoreDisplay.h";

ScoreDisplay::ScoreDisplay() : score(0), 
                               high_score(0),
                               score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHAR>()),
                               text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font))
                            )
{
}

void update()
{
    // increase score and update high score if this is the new highest
    score++;
    if (score > high_score)
    {
        high_score = score;
    }

    // Stop displaying previous scores
    score_sprites.clear();

    // Display new scores
    show_number(SCORE_X, SCORE_Y, score);
    show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);

    void show_number(int x, int y, int number)
        // Convert number to a string and then display it
        bn::string<MAX_SCORE_CHARS>
            number_string = bn::to_string<MAX_SCORE_CHARS>(number);
    text_generator.generate(x, y, number_string, score_sprites);
}
}
