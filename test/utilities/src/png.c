#include "utilities/png.h"

#include <stdlib.h>

#include "gd.h"
#include "spng.h"
#include "utils.h"

png_pixel_t png_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  png_pixel_t pixel;
  pixel.r = r;
  pixel.g = g;
  pixel.b = b;
  pixel.a = a;
  return pixel;
}

png_pixel_t png_color_random() {
  uint8_t r = rand() % 255;
  uint8_t g = rand() % 255;
  uint8_t b = rand() % 255;
  uint8_t a = 255;
  return png_color(r, g, b, a);
}

/**
 * @brief Allocate and initialize a new PNG type.
 *
 * @param width
 * @param height
 * @return png_t*
 */
png_t* new_png(uext_t width, uext_t height) {
  png_t* png = malloc(sizeof(png_t) + sizeof(png_pixel_t) * width * height);
  if (png == NULL) {
    goto out;
  }

  // set the attributes
  png->width = width;
  png->height = height;

out:
  return png;
}

/**
 * @brief Clean up an allocated PNG.
 *
 * @param png
 */
void release_png(png_t* png) { free(png); }

/**
 * @brief Write out a png image to a file.
 *
 * @param png
 * @param path
 * @return int
 */
int png_to_file(png_t const* png, char const* path) {
  int ret = 0;
  FILE* fp = NULL;
  spng_ctx* ctx = NULL;
  struct spng_ihdr ihdr;

  // check input pngs
  if (NULL == png) {
    ret = -1;
    goto out;
  }

  /* set png header */
  memset(&ihdr, 0U, sizeof(ihdr));
  ihdr.width = png->width;
  ihdr.height = png->height;
  ihdr.bit_depth = 8;
  ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

  // get spng context
  ctx = spng_ctx_new(SPNG_CTX_ENCODER);
  if (NULL == ctx) {
    ret = -1;
    goto out;
  }

  // open file
  fp = fopen(path, "w");
  if (fp == NULL) {
    ret = -1;
    goto cleanup_ctx;
  };

  // set the file in the png context
  ret = spng_set_png_file(ctx, fp);
  if (0 != ret) {
    printf("failed to set png file (code %d)", ret);
    goto cleanup_file;
  }
  ret = spng_set_ihdr(ctx, &ihdr);
  if (0 != ret) {
    printf("failed to set ihdr (code %d)", ret);
    goto cleanup_file;
  }

  /* encode png data */
  ret = spng_encode_image(
      ctx, &png->pixels, sizeof(png_pixel_t) * png->width * png->height,
      SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
  if (0 != ret) {
    printf("FAILED to encode png: '%s'\n", spng_strerror(ret));
  }

cleanup_file:
  fclose(fp);
cleanup_ctx:
  spng_ctx_free(ctx);
out:
  return ret;
}
