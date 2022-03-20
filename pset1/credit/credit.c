#include <stdio.h>
#include <cs50.h>

int check(long n);
int algorithm(int n[], int i);

int main(void)
{
    long n = get_long("Number:");
    while (n <= 0)
    {
        n = get_long("Number:");
    }
    check(n);
}

int check(long n)
{
    int number[16] = {0};
    int length = 0;
    
    // check if there are 13~16 digit numbers
    if (n < 1000000000000 || n >= 10000000000000000)
    {
        printf("INVALID\n");
        return 1;
    }
    
    // get each digit number
    while (n != 0)
    {
        number[length] = n % 10;
        n /= 10;
        length++;
    }
    length--;

    
    // count the first two numbers
    int head = number[length] * 10 + number[length - 1];
    
    
    // check American Express
    if (length == 14 && (head == 34 || head == 37))
    {
        if (algorithm(number, length) == 0)
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 1;
        }
    }
    
    // check MasterCard
    else if (length == 15 && (head >= 51 && head <= 55))
    {
        if (algorithm(number, length) == 0)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 1;
        }
    }
    
    // check VISA
    else if ((length >= 12 && length <= 15) && number[length] == 4)
    {
        if (algorithm(number, length) == 0)
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 1;
        }
        
    }
    
    else
    {
        printf("INVALID\n");
        return 1;
    }
}

int algorithm(int n[], int i)
{
    int flag = 0;
    int sum = 0;
    for (int j = 0; j <= i; j++)
    {
        if (flag == 0)
        {
            sum += n[j];
            flag = 1;
        }
        else if (flag == 1)
        {
            int temp = n[j] * 2;
            while (temp > 0)
            {
                sum += temp % 10;
                temp /= 10;
            }
            flag = 0;
        }
    }
    
    if (sum % 10 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

