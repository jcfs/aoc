#include <stdio.h>
#include <string.h>

char o[1000000000];
char d[1000000000];

int main(int argc, char ** argv) {

    int i, j;
    int count;
    char ch;
    int bw;

    char * src, * dst, * s;    

    sprintf(o, "%s", "1321131112");

    src = o;
    dst = d;

    for(j = 0; j <= 50; j++) {
        s = src;
        printf("%d %d\n", j, strlen(s)); 
        for(bw = 0, i = 0, count = 1; s[i]; ) {
            ch = s[i];
            if (ch == s[++i])
                count++;
            else {
                bw += sprintf(dst + bw, "%d%c", count, ch);
                count = 1;
            }
        }

        src = dst;
        dst = s;
    }
}
