#include <stdio.h>

#define GRID_SIZE 100

char m[GRID_SIZE][GRID_SIZE];
char t[GRID_SIZE][GRID_SIZE];

int count_n_on(int pos1, int pos2) {
    int count = 0;

    if (pos1 > 0 && pos2 > 0 && m[pos1-1][pos2-1] == '#') count++;
    if (pos2 > 0 && m[pos1][pos2-1] == '#') count++;
    if (pos2 > 0 && pos1 < GRID_SIZE-1 && m[pos1+1][pos2-1] == '#') count++;
    if (pos1 > 0 && m[pos1-1][pos2] == '#') count++;
    if (pos1 < GRID_SIZE -1 && m[pos1+1][pos2] == '#') count++;
    if (pos1 > 0 && pos2 < GRID_SIZE-1 && m[pos1-1][pos2+1] == '#') count++;
    if (pos2 < GRID_SIZE -1 && m[pos1][pos2+1] == '#') count++;
    if (pos1 < GRID_SIZE -1 && pos2 < GRID_SIZE -1 && m[pos1+1][pos2+1] == '#') count++;

    return count;
}

char calc_on_of(char onof, int pos1, int pos2) {
    int count = count_n_on(pos1, pos2);

    char r;

    if (onof == '#') {
        if (count == 2 || count == 3) 
            r = '#';
        else 
            r = '.';
    } else if (onof=='.') {
        if (count == 3) r = '#';
        else r='.';
    }

    return r;
}

int main(int argc, char **argv) {
    int i, j, s;
    char ch;

    for(i = 0; i <GRID_SIZE; i++)
        for(j = 0; j <GRID_SIZE; j++) {
            ch = getchar();
            if (ch != '.' && ch != '#') ch=getchar();
            m[i][j] = ch;
            t[i][j] = ch;
        }

    m[0][0] = '#';
    m[0][GRID_SIZE-1] = '#';
    m[GRID_SIZE-1][0] = '#';
    m[GRID_SIZE-1][GRID_SIZE-1] = '#';

    for(s = 0; s < 100; s++) {
        for(i = 0; i < GRID_SIZE; i++) {
            for(j = 0; j < GRID_SIZE; j++) {
                t[i][j] = calc_on_of(m[i][j], i, j);
            }
        }
        for(i = 0; i < GRID_SIZE; i++) {
            for(j = 0; j < GRID_SIZE; j++) {
                m[i][j] = t[i][j];
            }
        }
        m[0][0] = '#';
        m[0][GRID_SIZE-1] = '#';
        m[GRID_SIZE-1][0] = '#';
        m[GRID_SIZE-1][GRID_SIZE-1] = '#';

        for(i = 0; i < GRID_SIZE; i++) {
            for(j = 0; j < GRID_SIZE; j++) {
                printf("%c", m[i][j]);
            }
            printf("\n");
        }
        printf("\n----------\n");
    }

    int yy = 0;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            if (m[i][j] == '#') yy++;
        }
    }
    printf("%d\n", yy);
}
