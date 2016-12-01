#include <stdio.h>

int min_t(int a, int b, int c) {
    return a < b ? (a < c ? a : c) : b < c ? b : c;
}

int main(int argc, char ** argv) {

    int l, w, h;
    int totalPaper = 0;

    while(scanf("%dx%dx%d\n", &l, &w, &h) != -1) {
        totalPaper += 2*l*w + 2*w*h + 2*h*l + min_t(l*w, l*h, w*h);
    }

    printf("%d\n", totalPaper);


}
