#include <stdio.h>

int array[20] = {1,6,13,13,14,16,18,18,20,24,30,33,35,35,41,42,44,45,48,50};

int min = 10000;
int r = 150;
int total, times = 0;

int fill(int current, int c, int cont) {
    int i = 0;

    if (current == r) {
        if (cont < min) {
            times = 1;
            min = cont;
        }
        else if (cont == min) times++;
        total++;
        return;
    }

    for(i=c+1;i<20;i++) {
        if (current + array[i] <= r)
           fill(current + array[i], i, cont + 1);
    }
}

int main(int argc, char ** argv) {
    int i = 0;

    for(i = 0; i <20; i++) {
        fill(array[i], i, 1);
    }

    printf("min:%d total:%d total_min:%d\n", min, total, times);
}
