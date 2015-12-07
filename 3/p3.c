#include <stdio.h>
#include <unistd.h>

char m[9000][9000];

int move(char ch, int * x, int * y) {
    if (ch == '^') (*y)--;
    if (ch == 'v') (*y)++;
    if (ch == '<') (*x)--;
    if (ch == '>') (*x)++;
}

void print(int lower_x, int lower_y, int higher_x, int higher_y, int santa_x, int santa_y, int robot_x, int robot_y) {
    int i, j;

    printf("\e[1;1H\e[2J\x1B[0m");
    for(i = lower_x; i<higher_x+1; i++) {
        for(j = lower_y; j<higher_y+1; j++) {
            if (i == santa_x && j == santa_y) printf("#");
            else if (i == robot_x && j == robot_y) printf("@");
            else if (m[i][j]) printf("\x1B[31mx\x1B[0m");
            else printf("\x1B[32mX\x1B[0m");
        }
        printf("\n");
    }
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

    int lower_x = 10000, lower_y = 10000;
    int higher_x = 0, higher_y = 0;

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
            m[x][y]=(index%2)? 1 : 2;
        } else {
            m[x][y]=3;
        }

        if (x < lower_x) lower_x = x;
        if (x > higher_x) higher_x = x;

        if (y < lower_y) lower_y = y;
        if (y > higher_y) higher_y = y;

        print(lower_x, lower_y, higher_x, higher_y, santa_x, santa_y, robot_x, robot_y);

        usleep(80000);
        index++;
    }


    printf("%d\n", houses);
}
