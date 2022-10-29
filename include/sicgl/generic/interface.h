#pragma once

#include "sicgl/color.h"
#include "sicgl/display.h"
#include "sicgl/extent.h"
#include "sicgl/screen.h"

// sicgl needs implementations of various writer functions which
// allow it to actually interact with the user application
// a user defined implementation for 'pixel' is required. this
// implementation may be used to inform default 'naive' sicgl
// implementations of the other functions.
typedef void (*pixel_fn_t)(void* arg, color_t color, uext_t u, uext_t v);
typedef void (*hline_fn_t)(
    void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
typedef void (*vline_fn_t)(
    void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);
typedef void (*region_fn_t)(
    void* arg, color_t color, uext_t u0, uext_t v0, uext_t u1, uext_t v1);

// a generic interface give the user full flexibility
// at the expense of speed
typedef struct _generic_interface_t {
  pixel_fn_t pixel;
  hline_fn_t hline;
  vline_fn_t vline;
  region_fn_t region;

  // argument provided to functions
  void* arg;

  // hardware display information (used for clipping)
  display_t display;
  screen_t screen;
} generic_interface_t;