#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string fullName;

    bool itsOk = true;
    do
    {
        fullName = get_string();
        itsOk = true;
//checking for input the letters
        for (int i = 0, n = strlen(fullName); i < n; i++)
        {
            if ((isalpha(fullName[i]) == false) && ((int)fullName[i] != 32))
            {
                itsOk = false;
                i = n - 1;
            }
        }
    }
    while ((fullName == NULL) || (itsOk == false));

        for (int i = 0, n = strlen(fullName); i < n; i++)
        {
            if ((i == 0) && (isalpha(fullName[i])))
            {
                printf("%c", toupper(fullName[i]));
            }
            else
            {
                if (((int)fullName[i] == 32) && ((int)fullName[i+1] != 32) && (i != n - 1))
                {
                  printf("%c", toupper(fullName[i+1]));
                }
            }
        }
        printf("\n");
}