/* compile gcc -o p1 p1.c -Wall -O3 */
/* solution for both part1 and part 2 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

char input[31337];

uint32_t k = 0;
uint32_t max = 0;
uint32_t min = -1;

int8_t moves[4][3] = {
  { 0,-1,'U'},
  { 0, 1,'D'},
  {-1, 0,'L'},
  { 1, 0,'R'},
};

char * md5(const char *str, int length) {
  unsigned char digest[16];
  char * cs = (char *) malloc(33);

  MD5_CTX c;
  MD5_Init(&c);
  MD5_Update(&c, str, length);
  MD5_Final(digest, &c);

  for (int n = 0; n < 16; ++n) 
    snprintf(cs + n*2, 16*2, "%02x", (unsigned int) digest[n]);

  return cs;
}

// DFS 
void solve(int x, int y, int steps, char ch) {
  // append the current move to the input
  if (ch) input[k++] = ch;

  // we reach our final position lets update our min and max
  if (x == 3 && y == 3) {
    max = (steps > max) ? steps : max;
    (steps < min) ? (min = steps) && printf("new min(%d): %s\n", min, input+8) : 0;
    input[--k] = 0;
    return;
  }

  char * md = md5(input, strlen(input));
  // try every possible and valid moves
  for(int i = 0; i < 4; i++) {
    int xt = x + moves[i][0];
    int yt = y + moves[i][1];

    if (xt >= 0 && xt <= 3 && yt >= 0 && yt <= 3)
      if (md[i] >= 'b' && md[i] <= 'f') 
        solve(xt, yt, steps + 1, moves[i][2]);
  }
  
  // because we care
  free(md);

  // backtrack and remove the current move from the input
  if (ch) input[--k] = 0;
}


int main(int argc, char ** argv) {
  char * in = "pslxynzg";
  memcpy(input, in, strlen(in));
  k = strlen(input);
  solve(0, 0, 0, 0);
  printf("min: %d max: %d\n", min, max);
}
