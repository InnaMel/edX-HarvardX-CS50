#include <cs50.h>
#include <stdio.h>

int main (void)
{
    printf("Minutes: ");
    int min = 0;
    do
    {
        min = get_int();
      //  printf("Retry: ");
    }
    while (min <= 0);
    printf("Bottles: %i\n", min * 12);

}