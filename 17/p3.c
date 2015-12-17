#include <stdio.h>
int reach = 25;

int array[5] = {5,5,10,15,20};

int total = 0;
int min = 10000;
int times = 0;

int fill(int current, int c, int cont) {
    int i = 0;

    if (current > reach) return;

    if (current == reach) {
        
        if (cont < min) {
            times = 1;
            min = cont;
        }
        else if (cont == min) times++;
        printf("NEW TOTAL %d\n", current);
        total++;
        return;
    }

    for(i=c;i<5;i++) {
        if (array[i] != -1) {
            int g = array[i];
            array[i] = -1;
            fill(current + g, i, cont + 1);
            array[i] = g;
        }
    }
}

int main(int argc, char ** argv) {
    int i = 0;

    for(i = 0; i <5; i++) {
        int g = array[i];
        array[i] = -1;
        fill(g, i, 1);
        array[i] = g;
    }

    printf("%d\n", total);
    printf("%d\n", times);

}
