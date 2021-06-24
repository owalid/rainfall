
#include <stdlib.h>
#include <stdio.h>

int flag;

int main (void) {
 char buf[16];
 flag = 0;

 gets(buf);
 printf (buf);
 printf("flag: %i\n", flag);
 if (flag)
	 printf("You reached me!\n");

 return 0;
}
