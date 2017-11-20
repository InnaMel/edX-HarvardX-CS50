#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int AsciiAlphabetAscii(int deltaIn, int letterIn, int kIn);

int main(int argc, string argv[])
{
    int delta = 0;
    if (argc != 2)
    {
//        printf("Wrong argument\n");
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int k = atoi(argv[1]);

//    printf("key is %i\n", k);
    printf("plaintext: ");
    string plainTxt = get_string();

    printf("ciphertext: ");
    for (int i = 0, l = strlen(plainTxt); i < l; i++)
    {
        if (isalpha(plainTxt[i]))
        {
            if (isupper(plainTxt[i]))
            {
                delta = 65;
            }
            else
            {
                delta = 97;
            }
            plainTxt[i] = AsciiAlphabetAscii(delta, (int)(plainTxt[i]), k);
        }
        printf("%c", plainTxt[i]);
    }
    printf("\n");
    return 0;
}

int AsciiAlphabetAscii(int deltaIn, int letterIn, int kIn)
{
    int shiftLetter = 0;
    shiftLetter = (((letterIn - deltaIn) + kIn) % 26) + deltaIn;

    return shiftLetter;
}
