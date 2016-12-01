#include <stdio.h>
void main() {
    int v[]={50,44,11,49,42,46,18,32,26,40,21,7,18,43,10,47,36,24,22,40};
    unsigned int cnt=0, i, min=20;
    for(i=0; i<(1<<20); i++) {
        int j,sum=0;
        for (j=0; j<20; j++)
            if ((1 << j) & i) sum += v[j];
        if (sum == 150) {
            int bits = __builtin_popcount(i);
            if (bits < min) {
                min = bits;
                cnt = 1;
            } else if (bits == min) cnt++;    
        }
    }
    printf("%d\n", cnt);
}
