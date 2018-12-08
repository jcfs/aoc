#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node ** children;
  int n_children;
  int n_meta;
  int meta[100];
} node;

node * root;

void build(node * n) {
  int c, m;
  scanf("%d %d", &c, &m);

  n->n_children = c;
  n->n_meta = m;

  if (c) {
    n->children = calloc(c, sizeof(node*));
    for(int i = 0; i < c; i++) {
      n->children[i] = calloc(1, sizeof(node));
      parse(n->children[i]);
    }
  }
  
  for(int i = 0; i < m; i++) {
    int t = 0;
    scanf("%d", &t);
    n->meta[i] = t;
  }
}

int calc(node * n) {
  int v = 0;
  if (!n->n_children) {
    for(int i = 0; i < n->n_meta; i++) {
      v += n->meta[i];
    }
  } else {
    for(int i = 0; i < n->n_meta; i++) {
      int k = n->meta[i]-1;
      if (k < n->n_children) {
        v += calc(n->children[k]);
      }
    }
  }

  return v;
}


int main() {
  root = calloc(1, sizeof(node));
  build(root);
  printf("%d\n", calc(root));
}
