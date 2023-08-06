#include "error.h"

#include <string.h>

char err_msg[4096] = {0};

const char *get_error() {
    return err_msg;
}
