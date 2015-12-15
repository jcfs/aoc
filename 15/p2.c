#include <stdio.h>

int spoons[4] = {0};
int totals[5] = {0};

int main(int argc, char ** argv) {
    int i, j, k, w, u, r;
    int ing, pop;
    int t1, t2, t3, t4;
    long long max = -1, mul;

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

                if (i*input[0][4]+j*input[1][4]+k*input[2][4]+w*input[3][4] != 500) continue;

                for(u = 0; u < 4; u++) 
                    totals[u] = 0;

                for(r = 0; r < 4; r++) {
                    for(u = 0; u < 4; u++) {
                        totals[r] += spoons[u] * input[u][r];
                    }
                }

                mul = 1;
                for(u = 0; u < 4; u++) {
                    if (totals[u] < 0) 
                        totals[u] = 0;
                    mul *= totals[u];
                }

                if (mul > max) {
                    printf("%d %d %d %d=%lld : spoons %d %d %d %d\n", totals[0], totals[1], totals[2], totals[3], mul, i, j, k, w);
                    max = mul;
                }


            }


    printf("%ld\n", max);
}
