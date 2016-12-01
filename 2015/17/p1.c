#include <stdio.h>

int reach = 150;
int array[20] = {6,13,13,14,16,18,18,20,24,30,33,35,35,41,42,44,45,48,50,1};
int total = 0;

int fill(int current, int c) {
    int i = 0;
    if (current > reach) return;

    if (current == reach) {
        total++;
        return;
    }

    for(i=c+1;i<20;i++) {
        fill(current + array[i], i);
    }
}


int main(int argc, char ** argv) {
    int i = 0;

    for(i = 0; i < 20; i++) {
        fill(array[i], i);
    }

    printf("%d\n", total);

}
