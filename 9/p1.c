#include <stdio.h>

int m[100][100];
char v[100];
int lpath, spath = 10000;
int p;

int all_visited() {
    int i = 0;
    for(i = 0; i <= p; i++) 
        if (!v[i]) return 0;
    return 1;
}

int sp(int s, int dist) {
    int i = 0;

    v[s] = 1;

    if (all_visited()) {
        if (dist > lpath) lpath = dist;
        if (dist < lpath) spath = dist;
    }

    for(i = 0; i <= p; i++) {
        if (m[s][i] && !v[i]) {
            a++;
            sp(i, dist + m[s][i]);
        }
    }
    v[s] = 0;
}

int main(int argc, char ** argv) {
    int i, s, d, c;

    while(scanf("%d %d %d\n", &s, &d, &c) != -1) {
        m[s][d] = m[d][s] = c;
        if (s > p) p = s;
        if (d > p) p = d;
    }

    for(i = 0; i <= p; i++) sp(i, 0);

    printf("%d %d\n", spath, lpath);
}
