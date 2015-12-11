#include <stdio.h>
#include <regex.h>  

void increase(char * str) {
    int i = 0;

    for(i = 7; i >= 0; i--) {
        str[i]++;
        if (str[i] > 'z') str[i] = 'a';
        else break;
    }
}


int main(int argc, char ** argv) {
    regex_t regex[3];
    char str[9];
    int i = 0;

    sprintf(str, "%s\0", "ixbxwxba");

    regcomp(&regex[0], ".*(abc|bcd|cde|def|efg|fgh|pqr|qrs|rst|stu|tuv|uvw|vwx|wxy|xyz).*", REG_EXTENDED);
    regcomp(&regex[1], ".*[ilo].*", REG_EXTENDED);
    regcomp(&regex[2], ".*([a-z])\\1.*([a-z])\\2.*", REG_EXTENDED);

    for(i = 0; ; i++) {
        if (!regexec(&regex[0], str, 0, NULL, 0) && regexec(&regex[1], str, 0, NULL, 0) && !regexec(&regex[2], str, 0, NULL, 0)) break;
        increase(str);
    }

    printf("%s\n", str);
}
