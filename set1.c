/* set1.c - Tests for challenges in set 1 of cryptopals */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"
#include "frequency.h"
#include "util.h"

void test_ch1() {
    printf("~~Testing challenge 1~~\n");

    char *hex_test_str =
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char *b64_test_str =
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    byte *bytes1 = decode_hex(hex_test_str, strlen(hex_test_str));
    char *str1 = as_string(bytes1, strlen(hex_test_str) / 2);
    char *b64_ret = hex_to_b64(hex_test_str, strlen(hex_test_str));
    char *hex_ret = b64_to_hex(b64_test_str, strlen(b64_test_str));

    printf("Message is: %s\n", str1);

    assert(strcmp(b64_test_str, b64_ret) == 0);
    assert(strcmp(hex_test_str, hex_ret) == 0);

    free(bytes1);
    free(str1);
    free(b64_ret);
    free(hex_ret);
}

void test_ch2() {
    printf("~~Testing challenge 2~~\n");

    char *hex_buf1 = "1c0111001f010100061a024b53535009181c";
    char *hex_buf2 = "686974207468652062756c6c277320657965";
    char *expected_ret = "746865206b696420646f6e277420706c6179";
    int buflen = strlen(hex_buf1);

    byte *bytes1 = decode_hex(hex_buf1, buflen);
    byte *bytes2 = decode_hex(hex_buf2, buflen);
    byte *bytes_ret = fixed_xor(bytes1, bytes2, buflen / 2);
    char *str2 = as_string(bytes2, buflen / 2);
    char *str_ret = as_string(bytes_ret, buflen / 2);
    char *hex_ret = encode_hex(bytes_ret, buflen / 2);

    printf("Original message is: %s\n", str2);
    printf("Xor message is: %s\n", str_ret);

    assert(strcmp(hex_ret, expected_ret) == 0);

    free(bytes1);
    free(bytes2);
    free(bytes_ret);
    free(hex_ret);
    free(str2);
    free(str_ret);
}

void test_ch3() {
    printf("~~Testing challenge 3~~\n");

    char *chex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int chexlen = strlen(chex);

    byte *cbytes = decode_hex(chex, chexlen);

    /* Way bigger than any possible score from freq analysis */
    double best = 1000;
    char best_key;
    char *best_text = malloc(sizeof(char));
    for (int key = 0; key < 256; key++) {
        byte *dec_bytes = single_xor(cbytes, (char) key, chexlen / 2);
        char *dec_text = as_string(dec_bytes, chexlen / 2);
        double score = fa_score(dec_text);
        
        if (score < best && (int) strlen(dec_text) == chexlen / 2) {
            free(best_text);
            best = score;
            best_key = (char) key;
            best_text = dec_text;
        }
        else {
            free(dec_text);
        }
        
        free(dec_bytes);
    }

    printf("Decoded message is: %s\n", best_text);
    printf("Key was: %c\n", best_key);

    free(cbytes);
    free(best_text);
}

int main() {
    test_ch1();
    test_ch2();
    test_ch3();
    return 0;
}
