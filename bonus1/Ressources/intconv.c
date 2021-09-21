#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int lll, char **arg)
{
		int a;
		int b;

		a = atoi(arg[1]);
		b = a << 2;
		printf("a : %d , %p\n", a, &a);
		printf("b : %d , %p\n", b, &b);
		printf("\n");
}
