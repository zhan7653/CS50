#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    int number[26] = {0};
    int check[26] = {0};
    for (int i = 0, n = 0; i < 26; i++)
    {
        if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            number[i] = argv[1][i] - ('a' + i);
            n = argv[1][i] - 'a';
            check[n]++;
        }
        else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            number[i] = argv[1][i] - ('A' + i);
            n = argv[1][i] - 'A';
            check[n]++;
        }
        else
        {
            printf("Keys must be alphabetic characters.\n");
            return 1;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (check[i] != 1)
        {
            printf("Keys must be different characters.\n");
            return 1; 
        }
    }
    
    char *plain = get_string("plaintext: ");
    for (int j = 0, n = 0; plain[j] != '\0'; j++)
    {
        if (plain[j] >= 'a' && plain[j] <= 'z')
        {
            n = plain[j] - 'a';
            plain[j] += number[n];
        }
        else if (plain[j] >= 'A' && plain[j] <= 'Z')
        {
            n = plain[j] - 'A';
            plain[j] += number[n];
        }
    }
    
    printf("ciphertext: %s\n", plain);
    return 0;
    
}
