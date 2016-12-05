#include <stdio.h>
#include <openssl/md5.h>

int main(int argc, char ** argv)
{
	unsigned char c[MD5_DIGEST_LENGTH];
 	MD5_CTX mdContext;
	char out[64];
	char * format = "ugkcyxxp%d\0";
	int index = 1;
  char f[8] = {0};
  int i = 0;

  while(i < 8) {
    MD5_Init (&mdContext);
    snprintf(out, 64, format, index);
    MD5_Update (&mdContext, out, strlen(out));
    MD5_Final(c, &mdContext);

    if (!c[0] && !c[1] && !(c[2] & 0xF0)) {
      printf("%x", c[2]&0x0f);
      i++;
    }

    index++;
  }	
  printf("\n");

  return 0;
}
