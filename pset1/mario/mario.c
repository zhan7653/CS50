#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h = get_int("Height:");
    while (h <= 0 || h > 8)
    {
        h = get_int("Height:");
    }

    // print blocks of mario
    for (int i = h - 1; i >= 0; i--)
    {
        for (int k = 0; k < i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < h - i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < h - i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}