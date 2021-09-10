#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct internet {
    int priority;
    char *name;
};

void winner()
{
    printf("hello %d\n", time(NULL));
}

int main(int argc, char **argv)
{
    struct internet *i1, *i2, *i3;

    i1 = malloc(sizeof(struct internet));
    i1->priority = 1;
    i1->name = malloc(8);

    i2 = malloc(sizeof(struct internet));
    i2->priority = 1;
    i2->name = malloc(8);

    strcpy(i1->name, argv[1]);
	printf("addr: %p\n", i2->name);
    strcpy(i2->name, argv[2]);

    printf("and that's a wrap folks ! \n");
}
