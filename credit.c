#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkSummX2(int check)
{
    while (check >= 10)
    {
        check = (check / 10) + (check % 10);
    }
    return check;
}

int main (void)
{
    long long num = 0;
    int quantEven = 0, quantOdd = 0, inchNum = 0;
    bool even = false;
    do
    {
        printf("Number: ");
        num = get_long_long();
    }
    while ((num == LLONG_MAX) || (num < 0));

    long long numFull = num;

    while(num > 0)
    {
        if (even == false)
        {
            quantOdd += (num % 10);
            even = true;
        }
        else
        {
            quantEven += checkSummX2((num % 10) * 2);
            even = false;
        }
        inchNum ++;
        num /= 10;
    }

    if((inchNum < 13) || (inchNum > 16) || (((quantOdd + quantEven) % 10) != 0))
        {
            printf("INVALID\n");
        }
    else
        {
        if ((inchNum == 15) && (((numFull / 10000000000000) == 34) || ((numFull / 10000000000000) == 37)))
            {
                printf("AMEX\n");
            }
        else
            if ((inchNum == 16) && (((numFull / 100000000000000) == 51) || ((numFull / 100000000000000) == 52) || ((numFull / 100000000000000) == 53) || ((numFull / 100000000000000) == 54) || ((numFull / 100000000000000) == 55)))
            {
                printf("MASTERCARD\n");
            }
            else
            if  ( ((inchNum == 13) && (numFull / 1000000000000 == 4)) || ((inchNum == 16) && (numFull / 1000000000000000 == 4)))
            {
                printf("VISA\n");
            }
        }
    return 0;
}