#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char vigenerecode(int numLettTxt, int numLetterKey);
int fromLetterToNumAlphabet(char letterCurrent);
bool checkKey(string key);

int delta = 0;


int main(int argc, string argv[])
{
    if ((argc != 2) || (checkKey(argv[1]) == false))
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    string k = argv[1];
    int lengthKey = strlen(k);

    printf("plaintext: ");
    string plainTxt = get_string();
    int l = strlen(plainTxt);
    printf("ciphertext: ");
    for (int i = 0, j = 0; i < l; i++, j++)
    {
        if (isalpha(plainTxt[i]))
        {
            if (isupper(k[j]))
            {
                k[j] = (char)(tolower((int)k[j]));
            }
            plainTxt[i] = vigenerecode(fromLetterToNumAlphabet(k[j]), fromLetterToNumAlphabet(plainTxt[i]));
        }
        else
        {
            j--;
        }
        printf("%c", plainTxt[i]);
        if (j + 1 == lengthKey)
        {
            j = -1;
        }
    }
    printf("\n");
    return 0;
}

char vigenerecode(int numLetterKey, int numLettTxt)
{
    int shiftLetter = ((numLetterKey + numLettTxt) % 26) + delta;

    return (char)shiftLetter;
}

int fromLetterToNumAlphabet(char letterCurrent)
{
    delta = 0;
    if (isupper(letterCurrent))
    {
        delta = 65;
    }
    else
    {
        delta = 97;
    }
    int numAlphabet = (int)letterCurrent - delta;

    return numAlphabet;
}

bool checkKey(string key)
{
    bool rez = true;
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (isdigit(key[i]) != 0)
        {
            rez = false;
        }
    }
    return rez;
}
