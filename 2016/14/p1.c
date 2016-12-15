#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif
#include <stdlib.h>

#define null NULL

char * hashes[1001];
uint32_t indexes[1001];
uint32_t current_index;
int keys = 0;

char * md5(const char *str) {
  MD5_CTX c;
  unsigned char digest[16];
  char * out = (char*) calloc(33, sizeof(char));

  MD5_Init(&c);
  MD5_Update(&c, str, strlen(str));
  MD5_Final(digest, &c);

  for (int n = 0; n < 16; ++n) {
    snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
  }

  return out;
}

void generate_hash(char * s, uint32_t counter) {
  current_index = (current_index + 1 > 1000) ? 0 : current_index + 1;
  // because we care about memory much
  if (hashes[current_index] != null) {
    free(hashes[current_index]);
  }

  hashes[current_index] = md5(s);
  indexes[current_index] = counter;
}

bool has_triplet(char * str, char ch) {
  for(int i = 0; i < strlen(str) - 2; i++) {
    if (str[i] == str[i+1] && str[i] == str[i+2]) {
      if (str[i] == ch) 
        return true;
      else
        return false;
    }
  }
  return false;
}


int count_triplet(char ch, uint32_t * oi) {
  int i = current_index + 1, c = 0;
  for(int j = 0; j < 1000; j++, i++) {
    if (i > 1000) 
      i = 0;

    if (hashes[i] == null) 
      continue;

    if (has_triplet(hashes[i], ch)) {
      keys++;
      *oi = indexes[i];
      if (keys == 64) 
        return 1;
    }
  }

  return 1;
}

char has_f(char * str) {
  for(int i = 0; i < strlen(str) - 4; i++) {
    if (str[i] == str[i+1] && str[i] == str[i+2] && str[i] == str[i+3] && str[i] == str[i+4]) return str[i];
  }

  return 0;
}


int main(int argc, char ** argv) {
  char * input ="yjdafjpo%d";
  char buffer[64];
  uint32_t counter = 0;

  while(keys < 64) {
    sprintf(buffer, input, counter++);
    generate_hash(buffer, counter-1);

    char ch;
    if ((ch = has_f(hashes[current_index]))) {
      uint32_t oi;
      if (count_triplet(ch, &oi))
        printf("got key: %d %s %d\n", keys, hashes[current_index], oi);
    }
  }


}
