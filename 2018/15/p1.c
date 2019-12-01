#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE 100

char cpy[SIZE][SIZE];
char map[SIZE][SIZE];
int  dst[SIZE][SIZE];
int  hp[SIZE][SIZE];
unsigned char moved[SIZE][SIZE];
int maxx, maxy;

int calc(int eap, int verbose) {
  int i, j;
  int tx,ty;
  int d;
  int E = 0,G = 0;
  int ok;
  char cur, enemy;

  memcpy(cpy, map, sizeof(cpy));

  for (int y = 0; y < maxx; y++) {
    for (int x = 0; x < maxx; x++) {
      if (cpy[y][x] == 'G') {
        G++; 
        hp[y][x]=200;
      }
      if (cpy[y][x] == 'E') {
        E++; 
        hp[y][x]=200;
      }
    }
  }

  int t=0;

  while (1) {
    memset(moved, 0, sizeof(moved));

    for (int y = 0; y < maxx; y++) {
      for (int x = 0; x < maxx; x++) {
        if (moved[y][x]) continue;

        if (cpy[y][x]=='G' || cpy[y][x]=='E') {
          cur = cpy[j=y][i=x];
          enemy = cur ^ 'G' ^ 'E';

          if ((enemy == 'E' && !E) || (enemy == 'G' && !G)) {
            goto end;
          }

          if (cpy[y-1][x]!=enemy && cpy[y][x-1]!=enemy && cpy[y][x+1]!=enemy && cpy[y+1][x]!=enemy) {

            memset(dst,0,sizeof dst);
            dst[y][x]=1;
            d=1;

            do {
              ok = 0;
              for (j = 0; ok >= 0 && j < maxy; j++) {
                for (i = 0; ok >= 0 && i < maxy; i++) {
                  if (dst[j][i]==0
                      && cpy[j][i]=='.'
                      && (dst[j-1][i]==d || dst[j][i-1]==d || dst[j][i+1]==d || dst[j+1][i]==d)
                     ) {
                    dst[j][i]=d+1;

                    if (cpy[j-1][i]==enemy || cpy[j][i-1]==enemy || cpy[j][i+1]==enemy || cpy[j+1][i]==enemy) ok=-1;
                    else ok=1;
                  }
                }
              }
              d++;
            } while (ok>0);

            memset(dst, 0, sizeof(dst));
            dst[--j][--i]=1;
            d=1;

            while(ok && !dst[y][x]) {
              ok=0;
              for (j = 0; j < maxy; j++) {
                for (i = 0; i < maxy; i++) {
                  if (dst[j][i]==0 
                      && (cpy[j][i]=='.' || (j==y && i==x))
                      && (dst[j-1][i]==d || dst[j][i-1]==d || dst[j][i+1]==d || dst[j+1][i]==d)
                     ) ok=dst[j][i]=d+1;
                }
              }
              d++;
            } 
            if (ok) { 
              d--;
              if (dst[j=y-1][i=x]==d || dst[++j][--i]==d || dst[j][i+=2]==d || dst[++j][--i]==d) {
                cpy[j][i]=cpy[y][x];
                cpy[y][x]='.';
                hp[j][i]=hp[y][x];
                hp[y][x]=0;
              }
            }
            else continue;
          }

          moved[j][i]=1;
          unsigned mx = -1; 

          if (cpy[j-1][i] == enemy) mx = hp[ty=j-1][tx=i];
          if (cpy[j][i-1] == enemy && hp[j][i-1] < mx) mx = hp[ty=j][tx=i-1];
          if (cpy[j][i+1] == enemy && hp[j][i+1] < mx) mx = hp[ty=j][tx=i+1];
          if (cpy[j+1][i] == enemy && hp[j+1][i] < mx) mx = hp[ty=j+1][tx=i];

          if (mx != -1) {
            hp[ty][tx] -= (cur=='E'?eap:3);
            if (hp[ty][tx]<=0) {
              hp[ty][tx]=0;
              cpy[ty][tx]='.';
              
              if (enemy == 'E') E--; 
              else G--;

              if (enemy=='E' && !verbose) 
                return -1;
            }
          }
        }
      }
    }
    t++;
  }

end: 
  t+1;
  int total = 0;

  for (int y = 0; y < maxy; y++) {
    for (int x = 0; x < maxx; x++) {
      if (cpy[y][x] == 'E' || cpy[y][x] == 'G') 
        total += hp[y][x];
    }
  }

  printf("%d\n",total*t);
  return (E > 0) - (G > 0);
}

int main(int argc, char **argv) {
  int n;
  int eap;
  maxx = maxy = 0;
  
  while (fgets(&map[maxy][0], SIZE, stdin)) {
    n = strlen(map[maxy]);
    map[maxy][n-1]=0;

    maxy++;

    if (n > maxx) 
      maxx=n;
  }
  if (argc==2) eap=atoi(argv[1]);
  else for (eap=3; calc(eap, 0) < 0; eap++);

  calc(eap, 1);
  return 0;
}


