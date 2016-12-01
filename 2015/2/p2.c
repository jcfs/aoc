#include <stdio.h>

int min_t(int a, int b, int c) {
    return a < b ? (a < c ? a : c) : b < c ? b : c;
}

int main(int argc, char ** argv) {

    int l, w, h;
    int totalRibbon = 0;

    while(scanf("%dx%dx%d\n", &l, &w, &h) != -1) {
        totalRibbon += min_t((l+w)*2, (l+h)*2, (w+h)*2) + l*w*h;
    }

    printf("%d\n", totalRibbon);


}
