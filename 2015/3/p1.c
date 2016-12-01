#include <stdio.h>

int m[9000][9000];

int main(int argc, char **argv) {
    char ch;
    int current_x = 4500;
    int current_y = 4500;
    int houses = 1;

        int i = 0;
    m[current_x][current_y] = 1;

    while((ch = getchar()) != EOF) {
        if (ch == '^') current_y--;
        if (ch == 'v') current_y++;
        if (ch == '<') current_x--;
        if (ch == '>') current_x++;
        
        if (m[current_x][current_y] != 1) {
            houses++;
        }

        m[current_x][current_y] = 1;
    }

    printf("%d\n", houses);


}
