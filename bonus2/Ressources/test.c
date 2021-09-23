#include <string.h>
#include <stdio.h>

int main(int _, char **arg)
{
	char lol[10];

	strncpy(lol, arg[1], 10);
	printf("%s\n", lol);
}
