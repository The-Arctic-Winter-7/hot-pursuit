#pragma once

#include <bn_rect.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);