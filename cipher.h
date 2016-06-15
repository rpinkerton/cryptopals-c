/* cipher.h - header for cryptopals cipher functions */
#include "util.h"

byte *fixed_xor(byte *buf1, byte *buf2, int len);
byte *single_xor(byte *buf, byte key, int len);
char *single_xor_decode(char *chex);
