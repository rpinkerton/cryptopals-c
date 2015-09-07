/* frequency.c - simple frequency analysis */
#include <math.h>
#include <limits.h>

double en_freqs[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
                       0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
                       0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
                       0.06327, 0.09056, 0.02758, 0.00978, 0.02361, 0.00150,
                       0.01974, 0.00074};

double fa_score(char *text) {
    double dec_freqs[26] = {0};
    int total_chars = 0;
    int text_index = 0;
    int penalty = 0;
    
    /* Read all characters into array, then divide by total chars to get freq */
    while (text[text_index] != 0) {
        char ch = text[text_index];
        int ch_index = -1;

        if (65 <= ch && ch <= 90) {
            ch_index = (int) ch - 65;
        }
        else if (97 <= ch && ch <= 122) {
            ch_index = (int) ch_index - 97;
        }
        else if (ch != 34 || ch != 39 || ch != 32) {
            /* Penalty for using uncommon characters */
            penalty++;
        }

        if (ch_index != -1) {
            dec_freqs[ch_index]++;
            total_chars++;
        }

        text_index++;
    }

    if (total_chars == 0) {
        return INT_MAX;
    }

    double sum_sqrs = 0;

    /* Calculate Euclidean distance to standard freqs as score */
    for (int i = 0; i < 26; i++) {
        dec_freqs[i] /= total_chars;
        sum_sqrs += en_freqs[i] * pow(dec_freqs[i] - en_freqs[i], 2);
    }

    return sqrt(sum_sqrs) + penalty;
}
