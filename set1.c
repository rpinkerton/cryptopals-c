/* set1.c - Tests for challenges in set 1 of cryptopals */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

void test_ch1() {
    printf("Testing challenge 1\n");
    char *hex_test_str =
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char *b64_test_str =
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    printf("Message was: %s\n", decode_hex(hex_test_str, strlen(hex_test_str)));
    assert(b64_test_str = hex_to_b64(hex_test_str, strlen(hex_test_str)));
    assert(hex_test_str = b64_to_hex(b64_test_str, strlen(b64_test_str)));
}

int main() {
    test_ch1();
    return 0;
}
