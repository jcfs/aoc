
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <unistd.h>

int main(int argc, char **argv) {
    MD5Context c;
    unsigned char digest[16];
    char input[8] = "bgvyzdsv";
    int i = 1;

    while(i++) {
        MD5_Init(&c);
        MD5Update(&c, input, strlen(input));
        MD5Final(digest, &c);

        if (!strncmp(digest, "00000", 5)) {
            printf("%d\n", i);
        }
    }



}
