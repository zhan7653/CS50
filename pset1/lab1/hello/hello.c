#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *name = get_string("What's your name?\n");
    printf("Hello, %s.\n", name);
}