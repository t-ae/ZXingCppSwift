#include "include/cppstring.h"

extern "C" {

void cppstring_delete(cppstring * thiz) {
    delete thiz;
}

const char * cppstring_data(cppstring * thiz) {
    return thiz->data();
}

size_t cppstring_size(cppstring * thiz) {
    return thiz->size();
}

}
