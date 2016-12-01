#include <stdio.h>
#include <regex.h>

int main(int argc, char ** argv) {
        regex_t regex[2];
        char str[32];
        int count = 0;

        regcomp(&regex[0], ".*([a-z][a-z]).*\\1.*", REG_EXTENDED);
        regcomp(&regex[1], ".*([a-z])[a-z]\\1.*", REG_EXTENDED);

        while(scanf("%s\n", str) != -1) {
                if (!regexec(&regex[0], str, 0, NULL, 0) && !regexec(&regex[1], str, 0, NULL, 0)) count++;
        }

        printf("%d\n", count);
}
