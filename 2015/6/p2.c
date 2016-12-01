#include <stdio.h>

char world[1000][1000];

int main(int argc, char ** argv) {
	char inst[128];
	int xi, yi;
	int xf, yf;
	int i, j;
	int brightness = 0;

	while(scanf("%10[a-zA-Z ] %d,%d %s %d,%d\n", inst, &xi, &yi, inst+10, &xf, &yf) != -1) {
		int toggle = !strncmp(inst, "toggle", 6);
		int turn_off = !strncmp(inst, "turn off", 8);
		int turn_on = !strncmp(inst, "turn on", 7);

			for(i = xi; i <= xf; i++)
				for(j = yi; j <= yf; j++)
					if (toggle) { 
						world[i][j] += 2;
						brightness += 2;
					} 
					else if (turn_off) {
						brightness -= world[i][j] ? 1 : 0;
						world[i][j] -= world[i][j] ? 1 : 0;
					}
					else if (turn_on) {
						world[i][j]++;
						brightness++;
					}

	}
	
	printf("%d\n", brightness);
}
