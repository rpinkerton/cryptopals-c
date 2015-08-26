/* util.c - utility functions for cryptopals */
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

char *hex_to_b64(char *hex_str, int length) {
    byte *data = decode_hex(hex_str, length);
    char *b64 = encode_b64(data, length / 2);
    return b64;
}

char *b64_to_hex(char *b64_str, int length) {
    byte *data = decode_b64(b64_str, length);
    char *hex = encode_hex(data, 3 * length / 4);
    return hex;
}

int hex_char_to_int(char hex_char) {
    int val;

    /* Hex char is either number, letter, or capital */
    if (48 <= hex_char && hex_char <= 57) {
        val = (int) hex_char - 48;
    }
    else if (65 <= hex_char && hex_char <= 70) {
        val = (int) hex_char - 55;
    }
    else if (97 <= hex_char && hex_char <= 102) {
        val = (int) hex_char - 87;
    }
    else {
        val = -1;
    }

    return val;
}

char int_to_hex_char(int val) {
    char hex_char;

    if (0 <= val && val <= 9) {
        hex_char = (char) (val + 48);
    }
    else if (10 <= val && val <= 15) {
        hex_char = (char) (val + 55);
    }
    else {
        hex_char = (char) 0;
    }

    return hex_char;
}

byte *decode_hex(char *hex_str, int length) {
    if (length % 2 != 0) {
        printf("Invalid hex string: %s", hex_str);
        exit(1);
    }

    /* Two hex chars to a byte */
    byte *decoded = (byte *) malloc((length / 2) * sizeof(byte));

    for (int i = 0; i < length / 2; i++) {
        int byte_val = 0;
        byte_val += hex_char_to_int(hex_str[2 * i]) << 4;
        byte_val += hex_char_to_int(hex_str[2 * i + 1]);
        decoded[i] = byte_val;
    }

    return decoded;
}

char *encode_hex(byte *data, int length) {
    /* A byte is two hex chars */
    char *encoded = (char *) malloc((2 * length + 1) * sizeof(char));
    encoded[2 * length] = 0;

    for (int i = 0; i < length; i++) {
        encoded[2*i] = int_to_hex_char(data[i] >> 4);
        encoded[2*i + 1] = int_to_hex_char(data[i] & 15);
    }
    
    return encoded;
}

int b64_char_to_int(char b64_char) {
    int val;

    /* Hex char is either number, letter, capital, or (+, /) */
    if (65 <= b64_char && b64_char <= 90) {
        val = (int) b64_char - 65;
    }
    else if (97 <= b64_char && b64_char <= 122) {
        val = (int) b64_char - 71;
    }
    else if (48 <= b64_char && b64_char <= 57) {
        val = (int) b64_char + 4;
    }
    else if (b64_char == 43) {
        val = 62;
    }
    else if (b64_char == 47) {
        val = 63;
    }
    else {
        val = -1;
    }

    return val;
}

char int_to_b64_char(int val) {
    char b64_char;

    if (0 <= val && val <= 25) {
        b64_char = (char) (val + 65);
    }
    else if (26 <= val && val <= 51) {
        b64_char = (char) (val + 71);
    }
    else if (52 <= val && val <= 62) {
        b64_char = (char) (val - 4);
    }
    else if (val == 63) {
        b64_char = '+';
    }
    else if (val == 64) {
        b64_char = '/';
    }
    else {
        b64_char = (char) 0;
    }

    return b64_char;
}

byte *decode_b64(char *b64_str, int length) {
    if (length % 4 != 0) {
        printf("Invalid b64 string: %s", b64_str);
        exit(1);
    }

    /* Four b64 chars to 3 bytes */
    byte *decoded = (byte *) malloc((length / 4) * 3 * sizeof(byte));
    
    for (int i = 0; i < length / 4; i++) {
        /* Put the four chars into an int, the dispense into 3 bytes. */
        int bytes = 0;
        bytes += b64_char_to_int(b64_str[4 * i]) << 18;
        bytes += b64_char_to_int(b64_str[4 * i + 1]) << 12;
        bytes += b64_char_to_int(b64_str[4 * i + 2]) << 6;
        bytes += b64_char_to_int(b64_str[4 * i + 3]);
        decoded[3 * i] = bytes >> 16;
        decoded[3 * i + 1] = bytes >> 8 & 255;
        decoded[3 * i + 2] = bytes & 255;
    }

    return decoded;
}

char *encode_b64(byte *data, int length) {
    if (length % 3 != 0) {
        printf("Invalid data for converting to b64!");
        exit(1);
    }
        
    /* 3 bytes becomes four b64 characters */
    char *b64_str = (char *) malloc(((length / 3) * 4 + 1) * sizeof(char));
    b64_str[(length / 3) * 4] = 0;

    for (int i = 0; i < length / 3; i++) {
        /* Put 3 bytes into an int, then dispense into 4 characters. */
        int bytes = 0;
        bytes += data[3 * i] << 16;
        bytes += data[3 * i + 1] << 8;
        bytes += data[3 * i + 2];
        b64_str[4 * i] = int_to_b64_char(bytes >> 18);
        b64_str[4 * i + 1] = int_to_b64_char(bytes >> 12 & 63);
        b64_str[4 * i + 2] = int_to_b64_char(bytes >> 6 & 63);
        b64_str[4 * i + 3] = int_to_b64_char(bytes & 63);
    }

    return b64_str;
}
