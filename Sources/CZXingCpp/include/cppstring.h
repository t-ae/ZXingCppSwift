#pragma once

#include <stdio.h>

#ifdef __cplusplus
#include <string>
typedef std::string cppstring;
#else
struct _cppstring;
typedef struct _cppstring cppstring;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void cppstring_delete(cppstring * thiz);
const char * cppstring_data(cppstring * thiz);
size_t cppstring_size(cppstring * thiz);

#ifdef __cplusplus
}
#endif
