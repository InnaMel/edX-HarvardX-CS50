#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string fullName;
//    string ini;
    bool itsOk = true;
    do
    {
        fullName = get_string();
        itsOk = true;
//        strcpy(ini, &fullName[0]);
//        ini[0] = fullName[0];
        for (int i = 0, n = strlen(fullName); i < n; i++)
        {
            if (((toupper(fullName[i]) < 'A') || (toupper(fullName[i]) > 'Z')) && ((int)fullName[i] != 32))
            {
                itsOk = false;
                i = n - 1;
            }
        }
    }
    while ((fullName == NULL) || (itsOk == false));

        for (int i = 0, n = strlen(fullName); i < n; i++)
        {
            if (i == 0)
            {
                printf("%c", toupper(fullName[i]));
            }
            else
            {
                if (((int)fullName[i] == 32) && ((int)fullName[i+1] != 32))
                {
                  printf("%c", toupper(fullName[i+1]));
                }
            }
        }
        printf("\n");
}