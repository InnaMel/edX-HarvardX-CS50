#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while ((height < 0) || (height > 23));
    switch (height)
    {
        case 0:
            break;
        default:
        {
            int space = height - 1;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < (height + 1); j++)
                {
                    if (j < space)
                    {
                        printf(" ");
                    }
                    else
                        printf("#");
                }
                space--;
                printf("\n");
            }
        }
    }
}
