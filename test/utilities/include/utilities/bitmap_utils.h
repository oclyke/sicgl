// utilities for testing
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gd.h"
#include "sicgl.h"

// because truecolor alpha supports a smaller range of alphas the easiest move
// is to restrict the valid alpha values to [0, 127] for display these will be
// mapped back to the [0, 254] range but any comparisons will be done in the
// reduced range (to avoid off-by-one or incorrect range type)
#define PNG_ALPHA_FROM_TRUECOLOR_ALPHA(_tca) \
  (255 - (2 * ((_tca > 127) ? 127 : (_tca))))
#define TRUECOLOR_TRANSPARENT (127)
#define TRUECOLOR_OPAQUE (0)

/* values range from 0 to 255 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} bitmap_pixel_t;

typedef struct {
  size_t num_pix;
  size_t width;
  size_t height;
  bitmap_pixel_t pixels[];
} bitmap_t;

static inline void bitmap_free(bitmap_t* bitmap) { free(bitmap); }

static inline bitmap_t* bitmap_new(size_t width, size_t height) {
  size_t num_pix = width * height;
  bitmap_t* bm = malloc(sizeof(bitmap_t) + sizeof(bitmap_pixel_t) * num_pix);
  if (bm == NULL) {
    goto out;
  }

  bm->num_pix = num_pix;
  bm->width = width;
  bm->height = height;

out:
  return bm;
}

void bitmap_to_file(bitmap_t const* bitmap, char const* path);

static inline bitmap_pixel_t bmp_make_color(uint8_t r, uint8_t g, uint8_t b,
                                            uint8_t a) {
  bitmap_pixel_t pixel;
  pixel.r = r;
  pixel.g = g;
  pixel.b = b;
  pixel.a = a;
  return pixel;
}

static inline bitmap_pixel_t bmp_random_color() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  uint8_t a = 255;
  return bmp_make_color(r, g, b, a);
}

static inline int truecolor_random_color() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  uint8_t a = 255;
  return gdTrueColorAlpha(r, g, b, TRUECOLOR_OPAQUE);
}

// sicgl screenwriter functions
void bmp_pixel(void* arg, color_t color, uext_t u, uext_t v);
void bmp_hline(void* arg, color_t color, uext_t u0, uext_t v, uext_t u1);
void bmp_vline(void* arg, color_t color, uext_t u, uext_t v0, uext_t v1);