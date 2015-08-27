/* cipher.c - cipher functions for cryptopals */
#include <stdlib.h>
#include "util.h"

byte *fixed_xor(byte *buf1, byte *buf2, int length) {
    byte *ret_buf = malloc(length * sizeof(byte));
    
    for (int i = 0; i < length; i++) {
        ret_buf[i] = buf1[i] ^ buf2[i];
    }

    return ret_buf;
}
