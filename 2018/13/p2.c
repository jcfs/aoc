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
  char dead;
  char moved;
} cart;

cart carts[20];
int n_carts = 0;

void add(int x, int y, char dir) {
  carts[n_carts].x = x;
  carts[n_carts].y = y;
  carts[n_carts].direction = dir;
  n_carts++;
}

void rem(int x, int y) {
  for(int i = 0; i < n_carts; i++)
    if (carts[i].x == x && carts[i].y == y) carts[i].dead = 1;
}

int size() {
  int s = 0;
  for(int i = 0; i < n_carts; i++)
    if (!carts[i].dead) s++;

  return s;
}

cart * get(int x, int y) {

  for(int i = 0; i < n_carts; i++)
    if (!carts[i].moved && carts[i].x == x && carts[i].y == y) return &carts[i];

  return NULL;
}

int count(int x, int y) {
  int s = 0;              
  for(int i = 0; i < n_carts; i++)
    if (!carts[i].dead && carts[i].x == x && carts[i].y == y)
      s++;                  

  return s;               
}

char g[1000][1000];

int is_cart(char ch) {
  return ch == '<' || ch == 'v' || ch == '^' || ch == '>';
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

void print_r() {
  for(int i = 0; i < n_carts; i++)
    if (!carts[i].dead)
      printf("%d,%d %c %d\n", carts[i].x, carts[i].y, get_ch(carts[i].direction), carts[i].turn);
}

void print_m(int n, int ml) {
  for(int y = 0; y < n; y++) {
    for(int x = 0; x < ml; x++) {
      cart * t = get(x, y);
      if (t != NULL && !t->dead) {
        printf("%c", get_ch(t->direction));
      } else 
        printf("%c", g[y][x]);
    }
    printf("\n");
  }
}


char get_p(char ch) {
  if (ch == '<' || ch == '>') return '-';
  else return '|';
}

int step2(int ml, int n) {

  for(int i = 0; i < n_carts; i++) {
    cart * tmp = &carts[i];
    if (!tmp) continue;

    if (tmp->dead) {
      continue;
    }


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
      printf("CRASH %d, %d\n", tmp->x, tmp->y);
      rem(tmp->x, tmp->y);
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
          else if (tmp->direction == UP) tmp->direction = LEFT;
          else if (tmp->direction == DOWN) tmp->direction = RIGHT;
          else if (tmp->direction == LEFT) tmp->direction = DOWN;
        } else if (tmp->turn == 2) {
          if (tmp->direction == RIGHT) tmp->direction = DOWN;
          else if (tmp->direction == UP) tmp->direction = RIGHT;
          else if (tmp->direction == DOWN) tmp->direction = LEFT;
          else if (tmp->direction == LEFT) tmp->direction = UP;
        }

        tmp->turn++;
        if (tmp->turn > 2) {
          tmp->turn = 0;
        }
      }
    }
  }
}

int compare (const void * a, const void * b)
{

  cart *ca = (cart *)a;
  cart *cb = (cart *)b;

  if (ca->y == cb->y) return ca->x - cb->x;
  else ca->y - cb->y;
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
        g[y][x] = get_p(g[y][x]);
      }
    }
  }

  while(1) {
    qsort (carts, n_carts, sizeof(cart), compare);

    step2(ml, n);
    if (size() <= 1) {
      print_r();
      break;
    }
  }

}
