#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float Change = 0.0;
    int coin = 0;
    do
    {
        printf("Change owed:  ");
        Change = get_float();
    }
    while (Change < 0);

    Change = (Change * 100);
    int ChangeI = (int) roundf(Change);

    while (ChangeI > 0)
    {
        if ((ChangeI % 10 == 0.0) || (ChangeI % 5 == 0.0))
        {
            while (ChangeI >= 25)
            {
                ChangeI -= 25;
                coin++;
            }
            while (ChangeI >= 10)
            {
                ChangeI -= 10;
                coin++;
            }
            while (ChangeI >= 5)
            {
                ChangeI -= 5;
                coin++;
            }
        }
        else if (ChangeI != 0)
        {
            ChangeI--;
            coin++;
        }
    }
    printf("%i\n", coin);

}
