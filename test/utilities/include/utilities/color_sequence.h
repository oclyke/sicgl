#pragma once

#include "sicgl/color_sequence.h"

color_sequence_t* new_color_sequence(color_t* colors, size_t length);
int release_color_sequence(color_sequence_t* color_sequence);

int show_color_sequence(color_sequence_t* color_sequence);
