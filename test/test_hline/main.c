#include "sicgl.h"
#include "bitmap_utils.h"
#include "unity.h"

#include<stdio.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_hline(void) {
  const uext_t width = 255;
  const uext_t height = 255;

  // set up the interfaces
  // // a fast interface uses the bmp_vline implementation
  bitmap_t* fast_bm = bitmap_new(width, height);
  interface_t fast_intfc = {0};
  fast_intfc.screenwriter.arg = (void*)fast_bm;
  fast_intfc.screenwriter.pixel = bmp_pixel;
  fast_intfc.screenwriter.vline = bmp_vline;

  // // a naive interface only provides the bmp_pixel implementation
  bitmap_t* naive_bm = bitmap_new(width, height);
  interface_t naive_intfc = {0};
  naive_intfc.screenwriter.arg = (void*)naive_bm;
  naive_intfc.screenwriter.pixel = bmp_pixel;

  TEST_ASSERT_NOT_NULL(fast_bm);
  TEST_ASSERT_NOT_NULL(naive_bm);

  // draw some lines
  const uint32_t num_lines = 250;
  for (uint32_t count = 0; count < num_lines; count++) {
    uext_t v = rand() % height;
    uext_t u0 = rand() % width;
    uext_t u1 = rand() % width;
    bitmap_pixel_t pixel = bmp_random_color();

    // draw the pixel using the interfaces
    sicgl_draw_hline(&fast_intfc, (void*)&pixel, u0, v, u1);
    sicgl_draw_hline(&naive_intfc, (void*)&pixel, u0, v, u1);
  }

  // store images
  bitmap_to_file(fast_bm, "test_hline_fast.png");
  bitmap_to_file(naive_bm, "test_hline_naive.png");

  // compare the memory for the two images
  const size_t memory_len = sizeof(bitmap_pixel_t) * width * height;
  TEST_ASSERT_EQUAL_MEMORY (fast_bm->pixels, naive_bm->pixels, memory_len);

  // clean up
  bitmap_free(fast_bm);
  bitmap_free(naive_bm);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_hline);
  return UNITY_END();
}
