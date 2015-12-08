#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
    char line[128];
		int i = 0;	
		int count = 0;
	
    while(scanf("%s\n", line) != -1) {
			for(i = 0; i< strlen(line); i++) 
				if (line[i] == '\\' || line[i] == '\"') count++;
			count += 2;
		}   
		printf("%d", count);
}
