#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

int main(int argc, char ** argv) {
  unsigned char c[MD5_DIGEST_LENGTH];
  MD5_CTX mdContext;
  char out[64], f[8] = {0};
  char * format = "ugkcyxxp%d\0";
  int i = 0, j = 0;

  while(i < 8) {
    MD5_Init (&mdContext);
    snprintf(out, 64, format, j++);
    MD5_Update (&mdContext, out, strlen(out));
    MD5_Final(c, &mdContext);

    if (!c[0] && !c[1] && !(c[2] & 0xF0)) {
      if ((c[2]&0x0f) <= 7){
        if (f[c[2]&0x0f] == 0) {
          f[c[2]&0x0f] = ((c[3]&0xf0)>>4)+1;
          i++;
        }
      } 
    }
  }	

  for(i = 0; i < 8; i++) {
    printf("%x", f[i]-1);
  }

  return 0;
}
