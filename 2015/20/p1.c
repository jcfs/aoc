#include <stdio.h>
#include <math.h>

int main(int argc, char ** argv) {

  int i = 0;
  int count = 0;
  int house = 1;

  while(count < 29000000) {
    count = 0;

    for(i = 1; i <= sqrt(house); i++) {
      if (!(house % i)) {
        count+=i*10;
        if (i != (house/i)) {
          count+=(house/i)*10;
        }
      }
    }
    house++;
  }
  printf("%d %d\n", house-1, count);
}
