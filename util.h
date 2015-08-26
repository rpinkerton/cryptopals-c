/* util.h - header for cryptopals utility functions */

typedef unsigned char byte;

/* Direct translations */
char *hex_to_b64(char *hex_str, int length);
char *b64_to_hex(char *b64_str, int length);

/* Byte conversion */
byte *decode_hex(char *hex_str, int length);
byte *decode_b64(char *b64_str, int length);
char *encode_hex(byte *data, int length);
char *encode_b64(byte *data, int length);
