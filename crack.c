#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <crypt.h>
#include <ctype.h>

char salt[3];
string oldHash;
bool checkNewHashLonely(char myKey);
bool checkNewHash(string myKey);

bool checkKey0(void);
bool checkKey1(void);
bool checkKey2(void);
bool checkKey3(void);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Just one argument after ./crack\n");
        return 1;
    }

//get a hashpass from user******************
    oldHash = argv[1];

//take salt from hash (first two characters)*********************
    for (int i = 0; i < 2; i++)
    {
        salt[i] = oldHash[i];
    }

// i dont know what is it = int l = strlen(&myKey[5]); myKey[i] != '\0'
    if (checkKey0() || checkKey1() || checkKey2() || checkKey3())
    {
        //do nothing, yes you can
    }

    return 0;
}

//*********************************************************

bool checkNewHashLonely(char myKey)
{
    bool newCheck = true;
    string newHash = "";
    newHash = crypt(&myKey, salt);
    if (strcmp(oldHash, newHash) == 0)
    {
        printf("%c\n", myKey);
        newCheck = true;
    }
    else
    {
        newCheck = false;
    }
    return newCheck;
}

bool checkNewHash(string myKey)
{
    bool newCheck = true;
    string newHash = "";
    newHash = crypt(myKey, salt);
    if (strcmp(oldHash, newHash) == 0)
    {
        printf("%s\n", myKey);
        newCheck = true;
    }
    else
    {
        newCheck = false;
    }
    return newCheck;
}



// check by 1 letter ****************************************************************
bool checkKey0(void)
{
    char myKey;
    bool check = false;

    for (int i = 97; i <= 122; i++)
    {
//cheking in lowercase
        myKey = (char) i;
        check = checkNewHashLonely(myKey);
        if (check == true)
        {
            i = 123;
        }

//cheking in uppercase
        if (check == false)
        {
            myKey = toupper(myKey);
            check = checkNewHashLonely(myKey);
            if (check == true)
            {
                i = 123;
            }
        }
    }
    return check;
}




// ************************************************ check by 2 letter ************************************************************
bool checkKey1(void)
{
    char myKey[3];
    memset(myKey, 0, sizeof(myKey));
    bool check = false;

    for (int i = 97; i <= 122; i++)
    {
        for (int j = 97; j <= 122; j++)
        {

//cheking both in lowercase
            myKey[0] = (char) i;
            myKey[1] = (char) j;
            check = checkNewHash(myKey);
            if (check == true)
            {
                i = 123;
                j = 123;
            }

//cheking in aB uppercase
            if (check == false)
            {
                myKey[0] = (char) i;
                myKey[1] = toupper((char) j);
                check = checkNewHash(myKey);
                if (check == true)
                {
                    i = 123;
                    j = 123;
                }
            }
//cheking in Ab uppercase
            if (check == false)
            {
                myKey[0] = toupper((char) i);
                myKey[1] = (char) j;
                check = checkNewHash(myKey);
                if (check == true)
                {
                    i = 123;
                    j = 123;
                }
            }
//cheking in AB uppercase
            if (check == false)
            {
                myKey[0] = toupper((char) i);
                myKey[1] = toupper((char) j);
                check = checkNewHash(myKey);
                if (check == true)
                {
                    i = 123;
                    j = 123;
                }
            }


        }
    }
    return check;
}


// ************************************************ check by 3 letter ********************************************************************
bool checkKey2(void)
{
    char myKey[4];
    memset(myKey, 0, sizeof(myKey));
    bool check = false;

    for (int i = 97; i <= 122; i++)
    {
        for (int j = 97; j <= 122; j++)
        {
            for (int k = 97; k <= 122; k++)
            {

//cheking abc - all of three in lowercase
                myKey[0] = (char) i;
                myKey[1] = (char) j;
                myKey[2] = (char) k;
                check = checkNewHash(myKey);
                if (check == true)
                {
                    i = 123;
                    j = 123;
                    k = 123;
                }

//cheking in Abc
                if (check == false)
                {
                    myKey[0] = toupper((char) i);
                    myKey[1] = (char) j;
                    myKey[2] = (char) k;
                    check = checkNewHash(myKey);
                    if (check == true)
                    {
                        i = 123;
                        j = 123;
                        k = 123;
                    }
                }
//cheking in aBc
                if (check == false)
                {
                    myKey[0] = (char) i;
                    myKey[1] = toupper((char) j);
                    myKey[2] = (char) k;
                    check = checkNewHash(myKey);
                    if (check == true)
                    {
                        i = 123;
                        j = 123;
                        k = 123;
                    }
                }
//cheking in abC
                if (check == false)
                {
                    myKey[0] = (char) i;
                    myKey[1] = (char) j;
                    myKey[2] = toupper((char) k);
                    check = checkNewHash(myKey);
                    if (check == true)
                    {
                        i = 123;
                        j = 123;
                        k = 123;
                    }
                }
//cheking in ABC
                if (check == false)
                {
                    myKey[0] = toupper((char) i);
                    myKey[1] = toupper((char) j);
                    myKey[2] = toupper((char) k);
                    check = checkNewHash(myKey);
                    if (check == true)
                    {
                        i = 123;
                        j = 123;
                        k = 123;
                    }
                }
            }
        }
    }
    return check;
}

// ************************************************ check by 4 letter ********************************************************************
bool checkKey3(void)
{
    char myKey[5];
    memset(myKey, 0, sizeof(myKey));
    bool check = false;

    for (int i = 97; i <= 122; i++)
    {
        for (int j = 97; j <= 122; j++)
        {
            for (int k = 97; k <= 122; k++)
            {
                for (int t = 97; t <= 122; t++)
                {

//cheking abcd - all of them in lowercase
                    myKey[0] = (char) i;
                    myKey[1] = (char) j;
                    myKey[2] = (char) k;
                    myKey[3] = (char) t;
                    check = checkNewHash(myKey);
                    if (check == true)
                    {
                        i = 123;
                        j = 123;
                        k = 123;
                        t = 123;
                    }

//cheking in Abcd
                    if (check == false)
                    {
                        myKey[0] = toupper((char) i);
                        myKey[1] = (char) j;
                        myKey[2] = (char) k;
                        myKey[3] = (char) t;
                        check = checkNewHash(myKey);
                        if (check == true)
                        {
                            i = 123;
                            j = 123;
                            k = 123;
                            t = 123;
                        }
                    }
//cheking in aBcd
                    if (check == false)
                    {
                        myKey[0] = (char) i;
                        myKey[1] = toupper((char) j);
                        myKey[2] = (char) k;
                        myKey[3] = (char) t;
                        check = checkNewHash(myKey);
                        if (check == true)
                        {
                            i = 123;
                            j = 123;
                            k = 123;
                            t = 123;
                        }
                    }
//cheking in abCd
                    if (check == false)
                    {
                        myKey[0] = (char) i;
                        myKey[1] = (char) j;
                        myKey[2] = toupper((char) k);
                        myKey[3] = (char) t;
                        check = checkNewHash(myKey);
                        if (check == true)
                        {
                            i = 123;
                            j = 123;
                            k = 123;
                            t = 123;
                        }
                    }
//cheking in abcD
                    if (check == false)
                    {
                        myKey[0] = (char) i;
                        myKey[1] = (char) j;
                        myKey[2] = (char) k;
                        myKey[3] = toupper((char) t);
                        check = checkNewHash(myKey);
                        if (check == true)
                        {
                            i = 123;
                            j = 123;
                            k = 123;
                            t = 123;
                        }
                    }
//cheking in ABCD
                    if (check == false)
                    {
                        myKey[0] = toupper((char) i);
                        myKey[1] = toupper((char) j);
                        myKey[2] = toupper((char) k);
                        myKey[3] = toupper((char) t);
                        check = checkNewHash(myKey);
                        if (check == true)
                        {
                            i = 123;
                            j = 123;
                            k = 123;
                            t = 123;
                        }
                    }
                }
            }
        }
    }
    return check;
}
