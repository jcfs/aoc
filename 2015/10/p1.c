#include <stdio.h>
#include <string.h>

char o[10000000];
char d[10000000];

int main(int argc, char ** argv) {

    int i, j;
    int cnt, bw;
    char ch;
    char * src, * dst, * s;    

    sprintf(o, "%s", "1113222113");

    src = s = o;
    dst = d;

    for(j = 0; j < 50; s = src) {
        for(bw = 0, i = 0, cnt = 1; s[i]; ) {
            ch = s[i];
            if (ch == s[++i])
                cnt++;
            else {
                bw += sprintf(dst + bw, "%d%c", cnt, ch);
                cnt = 1;
            }
        }

        printf("%d %d\n", ++j, bw); 

        src = dst;
        dst = s;
    }
}
