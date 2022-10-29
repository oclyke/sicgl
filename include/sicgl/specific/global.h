#pragma once

#include "sicgl/specific/interface.h"
#include "sicgl/screen.h"

// draw in global coordinates
int sicgl_specific_global_pixel(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0);
int sicgl_specific_global_line(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_global_rectangle(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t u1, ext_t v1);
int sicgl_specific_global_circle_bresenham(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diameter);
int sicgl_specific_global_circle_ellipse(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t diameter);
int sicgl_specific_global_ellipse(
    specific_interface_t* interface,
    color_sequence_t* color_sequence, ext_t u0, ext_t v0, ext_t semiu, ext_t semiv);