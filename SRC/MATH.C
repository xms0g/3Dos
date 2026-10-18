#include "math.h"

#define LUT_SIZE 2048

static double sin_table[LUT_SIZE];
static double cos_table[LUT_SIZE];

static int calculate_index(double angle) {
    int idx = (int)(angle * (LUT_SIZE / TWO_PI));
    if (idx < 0) idx = 0;
    if (idx >= LUT_SIZE) idx = LUT_SIZE - 1;
    return idx;
}

double inv_sqrt(double n) {
    long i;
    float x2, y;

    x2 = n * 0.5F;
    y = n;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (x2 * y * y));   // 1st iteration
    y = y * (1.5f - (x2 * y * y));   // 2nd iteration

    return y;
}

void init_sincos_lut(void) {
    int i;
    // This function can be used to initialize any sine/cosine lookup tables if needed.
    // Currently, it does nothing as we are using the standard library functions.

    for (i = 0; i < LUT_SIZE; i++) {
        double rad = (i * TWO_PI) / LUT_SIZE;
        sin_table[i] = sin(rad);
        cos_table[i] = cos(rad);
    }
}

double sin_lut(double angle) {
    return sin_table[calculate_index(angle)];
}

double cos_lut(double angle) {
    return cos_table[calculate_index(angle)];
}