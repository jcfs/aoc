/* compile gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <stdint.h>
#include <string.h>


uint32_t SIZE=500;

uint32_t input = 1364, min = 50, count = 0;
uint8_t m[500][500];
int N = 0;
int k = 0;
int p[10][10];


// solve the problem recursivly (DFS)
void solve(uint8_t x, uint8_t y, uint8_t steps, uint8_t count, char ch, char t) {
  // if the current steps is greater than the desired min
  // we don't need to proceed any further
  if (steps > min) 
    return;


//  printf("%d, %d -> ", x, y, steps);
  // check the visited matrix to see if this is a new location
  
  if (ch == t) {
    if (steps < min) min = steps;
    return;
  }

  char ch1 = 0;
  if (x < 255 && m[y][x+1] != '#') {
    ch1 = m[y][x+1];
    m[y][x+1] = '#';
    solve(x+1, y, steps+1, count, ch1, t);
    m[y][x+1] = ch1;
  }
  if (y < 255 && m[y+1][x] != '#') {
    ch1 = m[y+1][x];
    m[y+1][x] = '#';
    solve(x, y+1, steps+1, count, ch1, t);
    m[y+1][x] = ch1;

  }
  if (x > 0 && m[y][x-1] != '#') {
    ch1 = m[y][x-1];
    m[y][x-1] = '#';
    solve(x-1, y, steps+1, count, ch1, t);
    m[y][x-1] = ch1;
  }
  if (y > 0 && m[y-1][x] != '#') {
    ch1 = m[y-1][x];
    m[y-1][x] = '#';
    solve(x, y-1, steps+1, count, ch1, t);
    m[y-1][x] = ch1;
  }

//  puts("");
  return;
}

int my = 10000;

int v[10];

int all() {
  for(int j = 0; j < 10; j++) if (v[j] < 0) return 0;

  return 1;
}


void sp(int y, int s) {
  v[y] = 1;

  if (all()) {
    if (s < my) my =s;
    v[y] = -1;
    return;
  }

  for(int j = 0; j < 10; j++) {
    if (v[j] < 0 && p[y][j] > 0) {
      sp(j, s+p[y][j]);
    }
  }

  v[y] = -1;
}

int main(int argc, char ** argv) {
  char c[1000];

  while(fgets(c, 1000, stdin)) {
    SIZE = strlen(c)-1;
    for(int i = 0; i < strlen(c); i++) {
      if (c[i] == '#') m[i][k] = '#';
      else m[i][k] = c[i];
    }
    k++;
  }

  int x1, y1, x2, y2;

  for(char ch1 = '0'; ch1 <= '6'; ch1++) {
    for(char ch2 = ch1+1; ch2 <= '7'; ch2++) {
      for(int x = 0; x < SIZE; x++) 
        for(int y = 0; y < SIZE; y++) {
          if (m[x][y] == ch1) {
            x1 = x;
            y1 = y;
          }
        } 

      for(int x = 0; x < SIZE; x++) 
        for(int y = 0; y < SIZE; y++) {
          if (m[x][y] == ch2) {
            x2 = x;
            y2 = y;
          }
        } 
      min = 80;
      solve(y1, x1, 0, 0, ch1, ch2);
      p[ch1-'0'][ch2-'0'] = min;
      p[ch2-'0'][ch1-'0'] = min;
      v[ch1-'0']=-1;
      v[ch2-'0']=-1;
      printf("From %c (%d,%d) to %c (%d,%d) the min is: %d\n", ch1, y1,x1,ch2,x2,y2, min);
    }
  }


  for(int i = 0; i <= 6; i++) {
    for(int j = i+1; j <= 7; j++) {
      printf("%d, %d -> %d\n", i, j, p[i][j]);
    }
  }

  sp(0, 0);
  printf("%d\n", my);
}
