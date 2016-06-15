/* cipher.c - cipher functions for cryptopals */
#include <stdlib.h>
#include <string.h>
#include "frequency.h"
#include "util.h"

byte *fixed_xor(byte *buf1, byte *buf2, int length) {
    byte *ret_buf = malloc(length * sizeof(byte));

    for (int i = 0; i < length; i++) {
        ret_buf[i] = buf1[i] ^ buf2[i];
    }

    return ret_buf;
}

byte *single_xor(byte *buf, byte key, int length) {
    byte *ret_buf = malloc(length * sizeof(byte));

    for (int i = 0; i < length; i++) {
        ret_buf[i] = buf[i] ^ key;
    }

    return ret_buf;
}

char *single_xor_decode(char *chex) {
    int chexlen = strlen(chex);

    byte *cbytes = decode_hex(chex, chexlen);

    /* Way bigger than any possible score from freq analysis */
    double best = 1000;
    char *best_text = malloc(sizeof(char));
    for (int key = 0; key < 256; key++) {
        byte *dec_bytes = single_xor(cbytes, (char) key, chexlen / 2);
        char *dec_text = as_string(dec_bytes, chexlen / 2);
        double score = fa_score(dec_text);

        if (score < best && (int) strlen(dec_text) == chexlen / 2) {
            free(best_text);
            best = score;
            best_text = dec_text;
        }
        else {
            free(dec_text);
        }

        free(dec_bytes);
    }

    free(cbytes);
    return best_text;
}
