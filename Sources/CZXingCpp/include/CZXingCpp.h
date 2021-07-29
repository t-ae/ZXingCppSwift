#pragma once

#include "cppstring.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

cppstring * qr_decode(const unsigned char* data, int cols, int rows, int format, int binarizer);

void qr_encode(const uint8_t* data, int length, int width, int height, uint8_t* image);

#ifdef __cplusplus
}
#endif
