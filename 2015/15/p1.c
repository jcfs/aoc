#include <stdio.h>

int spoons[4] = {0};
int totals[5] = {0};

int main(int argc, char ** argv) {
    int i, j, k, w, u, r;
    long long max = 0, mul;

    int input[4][5] = { 
        {4, -2, 0, 0, 5},
        {0, 5, -1, 0, 8},
        {-1, 0, 5, 0, 6},
        {0, 0, -2, 2, 1}
    };

    for(i = 1; i <= 100; i++)
        for(j = 1; j <= 100-i; j++)
            for(k = 1; k <= 100-i-j; k++) {
                w = 100 - k - i -j;

                spoons[0] = i;
                spoons[1] = j;
                spoons[2] = k;
                spoons[3] = w;

                for(r = 0; r < 4; r++) {
                    totals[r] = 0;
                    for(u = 0; u < 4; u++) {
                        totals[r] += spoons[u] * input[u][r];
                    }
                }

                for(mul = 1, u = 0; u < 4; u++) {
                    if (totals[u] < 0) break;
                    mul *= totals[u];
                }

                if (mul > max) {
                    max = mul;
                }
            }
    printf("%ld\n", max);
}
