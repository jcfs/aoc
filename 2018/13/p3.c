#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


typedef struct c {
  int x, y;
  char direction;
  int turn;
  char p;
  struct c * next;
} cart;


cart * root = NULL;
cart * head = NULL;


void add(int x, int y, char dir) {
  cart * n = calloc(1, sizeof(cart));
  n->x = x;
  n->y = y;
  n->direction = dir;

  if (root == NULL) {
    root = n;
    head = n;
    return;
  }

  head->next = n;
  head = head->next;
}

void rem(int x, int y) {
  cart * tmp = root;
  cart * prev = NULL;

    while(tmp != NULL) {
      if (tmp->next != NULL) {
        if (tmp->x == x && tmp->y == y) {
          tmp->next = tmp->next->next;
        }
      } else {
        if (tmp->x == x && tmp->y == y) {
          if (prev == root) {
            root = NULL;
            head = NULL;
          } else {
            prev->next = tmp->next;
          }
        }
      }

      prev = tmp;
      if (tmp->next == NULL)
        head = tmp;

      tmp = tmp->next;
    }
}

int size() {
  int s = 0;
  cart * tmp = root;
  while(tmp != NULL) {
    s++;
    tmp = tmp->next;
  }

  return s;
}

int count(int x, int y) {
  int s = 0;              
  cart * tmp = root;      
  while(tmp != NULL) {    
    if (tmp->x == x && tmp->y == y)
      s++;                  
    tmp = tmp->next;      
  }                       

  return s;               
}

cart carts[1000];

char c[1000][1000];
char g[1000][1000];
char cpy[1000][1000];
int n_carts  = 0;

int is_cart(char ch) {
  return ch == '<' || ch == 'v' || ch == '^' || ch == '>';
}
int cnt(char ii[1000][1000]) {
  int r = 0;
  for(int  i = 0; i < 1000; i++)
    for(int  j = 0; j < 1000; j++)if(is_cart(ii[i][j])) r++;

  return r;
}


int get_dir(char ch) {
  if (ch == '<') return LEFT;
  if (ch == 'v') return DOWN;
  if (ch == '^') return UP;
  if (ch == '>') return RIGHT;
}

char get_ch(int dir) {
  if (dir == LEFT) return '<';
  if (dir == DOWN) return 'v';
  if (dir == UP) return '^';
  if (dir == RIGHT) return '>';
}

cart * get_cart(int x, int y) {

  for(int k = 0; k < 1000; k++) {
    if (carts[k].x == x && carts[k].y == y) return &carts[k];
  }

  printf("%d %d\n");
  printf("BANG~\n");
  return NULL;
}

char get_p(char ch) {
  if (ch == '<' || ch == '>') return '-';
  else return '|';
}

void copy(char src[1000][1000], char dst[1000][1000]) {
  for(int i = 0; i < 1000; i++)
    for(int j = 0; j < 1000; j++) {
      dst[i][j] = src[i][j];
    }
}

int step2(int ml, int n) {
  cart * tmp = root;

  while(tmp != NULL) {
//    printf("going to %d,%d\n", tmp->x, tmp->y);
    if (tmp->direction == RIGHT) {        
      tmp->x++;                    
    } else if (tmp->direction == LEFT) {  
      tmp->x--;                    
    } else if (tmp->direction == DOWN) {  
      tmp->y++;                    
    } else if (tmp->direction == UP) {    
      tmp->y--;                    
    }                          

    int c = count(tmp->x, tmp->y);
    if (c > 1) {
      printf("%d\n", size());
      cart * next = tmp;
      while(next != NULL && next->x == tmp->x && next->y == tmp->y) next = next->next;
      rem(tmp->x, tmp->y);
      tmp = next;
      printf(">> %d\n", size());
      continue;
    } else {
      int xf = tmp->x;
      int yf = tmp->y;
      if (g[yf][xf] == '\\') {
        if (tmp->direction == RIGHT) {
          tmp->direction = DOWN;
        } else if (tmp->direction == LEFT) {
          tmp->direction = UP;
        } else if (tmp->direction == UP) {
          tmp->direction = LEFT;
        } else if (tmp->direction == DOWN) {
          tmp->direction = RIGHT;
        }
      } else if (g[yf][xf] == '/') {
        if (tmp->direction == RIGHT) {
          tmp->direction = UP;
        } else if (tmp->direction == LEFT) {
          tmp->direction = DOWN;
        } else if (tmp->direction == UP) {
          tmp->direction = RIGHT;
        } else if (tmp->direction == DOWN) {
          tmp->direction = LEFT;
        }
      }

      char cy = g[yf][xf];

      if (cy == '+') {
        if (tmp->turn == 0) {
          if (tmp->direction == RIGHT) tmp->direction = UP;
          if (tmp->direction == UP) tmp->direction = LEFT;
          if (tmp->direction == DOWN) tmp->direction = RIGHT;
          if (tmp->direction == LEFT) tmp->direction = DOWN;
        } else if (tmp->turn == 2) {
          if (tmp->direction == RIGHT) tmp->direction = DOWN;
          if (tmp->direction == UP) tmp->direction = RIGHT;
          if (tmp->direction == DOWN) tmp->direction = LEFT;
          if (tmp->direction == LEFT) tmp->direction = UP;
        }

        tmp->turn++;
        if (tmp->turn > 2) tmp->turn = 0;
      }


    }


    tmp = tmp->next;
  }

}

int step(int n, int ml) {
  copy(g, cpy);
  int n_c = 0;
  for(int y = 0; y < n; y++) {
    for(int x = 0; x < ml; x++) {
      if (is_cart(g[y][x])) {
        cart * cc = get_cart(x, y);

        int dir = get_dir(g[y][x]);

        int xf = x;
        int yf = y;

        if (dir == RIGHT) {
          xf++;
        } else if (dir == LEFT) {
          xf--;
        } else if (dir == DOWN) {
          yf++;
        } else if (dir == UP) {
          yf--;
        }

        if (is_cart(cpy[yf][xf])) {
          cart * cc1 = get_cart(xf, yf);
          printf("%c %c %c %c\n", cpy[yf][xf], g[y][x], cc1->p, cc->p);

          cpy[yf][xf] = cc1->p;
          cpy[y][x] = cc->p;
          g[yf][xf] = cc1->p;

          continue;
        }
        n_c++;

        if (cpy[yf][xf] == '\\') {
          if (cc->direction == RIGHT) {
            cc->direction = DOWN;
          } else if (cc->direction == LEFT) {
            cc->direction = UP;
          } else if (cc->direction == UP) {
            cc->direction = LEFT;
          } else if (cc->direction == DOWN) {
            cc->direction = RIGHT;
          }
        } else if (cpy[yf][xf] == '/') {
          if (cc->direction == RIGHT) {
            cc->direction = UP;
          } else if (cc->direction == LEFT) {
            cc->direction = DOWN;
          } else if (cc->direction == UP) {
            cc->direction = RIGHT;
          } else if (cc->direction == DOWN) {
            cc->direction = LEFT;
          }
        }

        cpy[y][x] = cc->p;
        cc->p = g[yf][xf];
        cc->x = xf;
        cc->y = yf;


        if (cc->p == '+') {
          if (cc->turn == 0) {
            if (dir == RIGHT) cc->direction = UP;
            if (dir == UP) cc->direction = LEFT;
            if (dir == DOWN) cc->direction = RIGHT;
            if (dir == LEFT) cc->direction = DOWN;
          } else if (cc->turn == 2) {
            if (dir == RIGHT) cc->direction = DOWN;
            if (dir == UP) cc->direction = RIGHT;
            if (dir == DOWN) cc->direction = LEFT;
            if (dir == LEFT) cc->direction = UP;
          }

          cc->turn++;
          if (cc->turn > 2) cc->turn = 0;
        }

        cpy[yf][xf] = get_ch(cc->direction);

      }
    }
  }

  copy(cpy, g);
  return n_c;
}

int main() {
  int n = 0;
  int ml = 0;

  while(fgets(&g[n], 1000, stdin) != NULL) {
    n++;
  }

  for(int i = 0; i < n; i++) {
    g[i][strlen(g[i])-1] = 0;
    if (strlen(g[i]) > ml) {
      ml = strlen(g[i]);
    }
  }

  for(int y = 0; y < n; y++) {
    for(int x = 0; x < ml; x++) {
      if (is_cart(g[y][x])) {
        add(x, y, get_dir(g[y][x]));
        printf("%d,%d\n", x, y);
        g[y][x] = get_p(g[y][x]);
      }
    }
  }

  while(1) {
    step2(ml, n);
  }

}
