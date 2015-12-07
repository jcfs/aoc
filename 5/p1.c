#include <stdio.h>
#include <regex.h>  

int main(int argc, char ** argv) {
	regex_t regex[3];
	char str[32];
	int count = 0;
	
	regcomp(&regex[0], ".*(.*[aeiou]){3}.*", REG_EXTENDED);
	regcomp(&regex[1], ".*(.)\\1.*", REG_EXTENDED);
	regcomp(&regex[2], ".*(ab|cd|pq|xy).*", REG_EXTENDED);
	
	while(scanf("%s\n", str) != -1) {
		if (!regexec(&regex[0], str, 0, NULL, 0) && !regexec(&regex[1], str, 0, NULL, 0) && regexec(&regex[2], str, 0, NULL, 0)) count++;
	}

	printf("%d\n", count);
}
