#include <stdio.h>

char m[9000][9000];

int move(char ch, int * x, int * y) {
    if (ch == '^') (*y)--;
    if (ch == 'v') (*y)++;
    if (ch == '<') (*x)--;
    if (ch == '>') (*x)++;
}

int main(int argc, char **argv) {
    char ch;
    int x, y;
    int santa_x = 4500;
    int santa_y = 4500;
    int robot_x = 4500;
    int robot_y = 4500;
    int houses = 1;
    int index = 0;

    m[santa_x][santa_y] = 1;

    while((ch = getchar()) != EOF) {
        if (index % 2) {
            move(ch, &santa_x, &santa_y);
            x = santa_x;
            y = santa_y;
        } else {
            move(ch, &robot_x, &robot_y);
            x = robot_x;
            y = robot_y;
        }

        if (!m[x][y]) {
            houses++;
        }
        m[x][y]=1;

        index++;
    }

    printf("%d\n", houses);
}
