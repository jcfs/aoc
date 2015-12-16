#include <stdio.h>

int sue[500][10] = {-1};
int m[10] = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};

int main(int argc, char ** argv) {

    int i = 0, j = 0;
    int sue_number, prop1, val1, prop2, val2, prop3, val3;

    for(i = 0; i < 500; i++)
        for(j = 0; j < 10; j++) 
            sue[i][j] = -1;

    while(scanf("%d: %d: %d, %d: %d, %d: %d\n", &sue_number, &prop1, &val1, &prop2, &val2, &prop3, &val3) != -1) {
        sue[sue_number-1][prop1] = val1;
        sue[sue_number-1][prop2] = val2;
        sue[sue_number-1][prop3] = val3;
    }

    for(i = 0; i < 500; i++) {
        int * current = sue[i];

        char flag = 1;
        for(j = 0; j < 10; j++) {
            if (current[j] != -1) {

                if (j == 1 || j == 7) {
                    if (current[j] <= m[j]) {
                        flag = 0;
                        break;
                    }
                } else if (j == 3 || j == 6) {
                    if (current[j] >= m[j]) {
                        flag = 0;
                        break;
                    }
                } else if (current[j] != m[j]) {
                    flag = 0;
                    break;
                }
            }
        }

        if (flag) {
            printf("-> %d\n", i+1);
            break;
        }
    }
}
