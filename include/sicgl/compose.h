#pragma once

#include "sicgl/interface.h"
#include "sicgl/screen.h"

typedef void (*compositor_fn)(color_t* source, color_t* destination);
int sicgl_compose(
    interface_t* interface, screen_t* screen, color_t* sprite,
    compositor_fn compositor);
