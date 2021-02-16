#pragma once

#include "cppstring.h"

#ifdef __cplusplus
extern "C" {
#endif

cppstring * qr_decode(const unsigned char* data, int cols, int rows, int format);

#ifdef __cplusplus
}
#endif
