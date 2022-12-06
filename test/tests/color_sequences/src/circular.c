#include "sicgl/screen.h"
#include "utils.h"

void test_circular_case1(void) {
  uext_t width = 30;
  uext_t height = 3;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  display_t* display = NULL;
  specific_interface_t* interface = NULL;
  color_sequence_t* color_sequence = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    display = new_display(width, height, 0, 0);
    interface = new_libgd_specific_interface(display, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(display, "could not create display");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create a color sequence
    color_t red = 0x00ff0000;
    color_t blue = 0x000000ff;
    color_t colors[] = {red, blue};
    color_sequence =
        new_color_sequence(colors, sizeof(colors) / sizeof(color_t));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // draw an interpolated gradient hline
    int ret;
    for (size_t idu = 1; idu < width - 1; idu++) {
      color_t color;

      // determine the phase
      double phase = ((idu - 1) / (double)(width - 3));

      // perform the interpolation
      ret = color_sequence_get_color_circular(color_sequence, phase, &color);
      TEST_ASSERT_EQUAL_INT(0, ret);

      // draw a pixel at this location
      ret = simultaneous_specific_pixel(reference, interface, color, idu, 1);
      TEST_ASSERT_EQUAL_INT(0, ret);
    }

    // convert the interface to a test image
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/circular_case1_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/circular_case1_img.png"));

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_display(display);
    release_libgd_specific_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}

void test_circular_case2(void) {
  uext_t width = 30;
  uext_t height = 3;

  gdImage* reference = NULL;
  gdImage* image = NULL;
  display_t* display = NULL;
  specific_interface_t* interface = NULL;
  color_sequence_t* color_sequence = NULL;
  png_t* ref = NULL;
  png_t* img = NULL;

  if (TEST_PROTECT()) {
    // create images
    reference = new_image(width, height);
    TEST_ASSERT_NOT_NULL_MESSAGE(
        reference, "could not allocate reference image");

    // create specific interface
    display = new_display(width, height, 0, 0);
    interface = new_libgd_specific_interface(display, NULL, 0);
    TEST_ASSERT_NOT_NULL_MESSAGE(display, "could not create display");
    TEST_ASSERT_NOT_NULL_MESSAGE(interface, "could not create interface");

    // create a color sequence
    color_t red = 0x00ff0000;
    color_t blue = 0x000000ff;
    color_t cyan = 0x0000aaaa;
    color_t green = 0x0000ff00;
    color_t colors[] = {blue, red, cyan, green};
    color_sequence =
        new_color_sequence(colors, sizeof(colors) / sizeof(color_t));
    TEST_ASSERT_NOT_NULL_MESSAGE(
        color_sequence, "could not create color sequence");

    // draw an interpolated gradient hline
    int ret;
    for (size_t idu = 1; idu < width - 1; idu++) {
      color_t color;

      // determine the phase
      double phase = ((idu - 1) / (double)(width - 3));

      // perform the interpolation
      ret = color_sequence_get_color_circular(color_sequence, phase, &color);
      TEST_ASSERT_EQUAL_INT(0, ret);

      // draw a pixel at this location
      ret = simultaneous_specific_pixel(reference, interface, color, idu, 1);
      TEST_ASSERT_EQUAL_INT(0, ret);
    }

    // convert the interface to a test image
    image = new_image_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(image, "could not convert test image");

    // save images to png
    ref = new_png_from_image(reference);
    img = new_png_from_libgd_specific_interface(interface);
    TEST_ASSERT_NOT_NULL_MESSAGE(ref, "could not create ref png");
    TEST_ASSERT_NOT_NULL_MESSAGE(img, "could not create img png");
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(ref, TEST_OUTPUT_DIR "/circular_case2_ref.png"));
    TEST_ASSERT_EQUAL_INT(
        0, png_to_file(img, TEST_OUTPUT_DIR "/circular_case2_img.png"));

    // compare the images
    TEST_ASSERT_EQUAL_INT(0, compare_image(reference, image));

  } else {
    release_image(reference);
    release_image(image);
    release_display(display);
    release_libgd_specific_interface(interface);
    release_color_sequence(color_sequence);
    release_png(ref);
    release_png(img);
  }
}