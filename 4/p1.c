#include <stdio.h>
#include <openssl/md5.h>

int main(int argc, char ** argv)
{
	unsigned char c[MD5_DIGEST_LENGTH];
	char out[64];
	char * format = "bgvyzdsv%d\0";
	int index = 250000;

	while(1) {
		MD5_Init (&mdContext);
		snprintf(out, 64, format, index);
		MD5_Update (&mdContext, out, strlen(out));
		MD5_Final(c, &mdContext);

		if (!c[0] && !c[1] && !(c[2])) {
			break;
		}

		index++;
	}	

	printf("%d\n", index);
	return 0;
}
