#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET 26
//struct  __attribute__((__packed__)) dictStruct atributes for exactly summ byte
struct dictStruct
{
    int hash;
    char word[45];
    struct dictStruct *next;
};
typedef struct dictStruct DICTENTITY;

DICTENTITY
*hashTableDict[ALPHABET];    // my hash table (array of link list) for hashing dictionary массив 26 элементов

DICTENTITY *createNewEntity();
bool load(const char *dictionary);
bool unload(void);
int myHashFunction(char *word, int *fullHash);
void printDictionary();
bool check(char *word);
int quantityWords = 0;

//  main
int main(int argc, char *argv[])
{
    // check for correct number of args
    if (argc != 3)
    {
        printf("Usage: dictionary\n");
        return 1;
    }

    // dictionary to use: dictionaries/small
    char *dictionary = argv[1];

    // word to check: any word
    char *wordCheck = argv[2];

    load(dictionary);
    printDictionary();

    if (check(wordCheck))
    {
        printf("Word %s is present \n", wordCheck);
    }
    else
    {
        printf("Word %s isn`t present \n", wordCheck);
    }

    unload();

    return 0;

}

// loading dictionary in array of link list
bool load(const char *dictionary)
{
    bool result = false;
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile)
    {
//        printf("dictionary open successful \n");
        memset(hashTableDict, 0, ALPHABET * sizeof(DICTENTITY *));
        char everyWord[45];
        result = true;

        while (fscanf(dictFile, "%s", everyWord) != EOF)
        {
//            printf("Loading word: %s \n", everyWord);
            int hashStruct = 0;
            int currentHash = myHashFunction(everyWord, &hashStruct);
//            printf("Hash of %s: %d \n",everyWord, currentHash);
            DICTENTITY *newNextNode = createNewEntity();
            if (newNextNode == NULL)
            {
                result = false;
                // unload();
                break;
            }

            //fill new node
            strcpy(newNextNode->word, everyWord);
            newNextNode->hash = hashStruct;
            quantityWords++;

            //swap
            newNextNode->next = hashTableDict[currentHash];
            hashTableDict[currentHash] = newNextNode;
        }
        fclose(dictFile);
    }
    if (!result)
    {
        unload();
    }

    return result;
}


// unload
bool unload(void)
{
    if (quantityWords > 0)
    {
        for (int i = 0; i < ALPHABET; i++)
        {
            DICTENTITY *copyhashTableDict = hashTableDict[i];
            while (copyhashTableDict != NULL)
            {
                DICTENTITY *next = copyhashTableDict->next;     // create new entity for deleting step by step
                free(copyhashTableDict);
                copyhashTableDict = next;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}


// Creating new node. Ask memory from mamloc.
DICTENTITY *createNewEntity()
{
    DICTENTITY *result = malloc(sizeof(DICTENTITY));
    if (result == NULL)
    {
        return result;
    }

    memset(result, 0, sizeof(DICTENTITY));      // zero pointers

    return result;
}

// print
void printDictionary()
{
    printf("enter in print*************** \n");
    if (quantityWords > 0)
    {
        // create copy of ptr needed index LL
        for (int i = 0; i < ALPHABET; i++)
        {
            if (hashTableDict[i] != NULL)
            {
                DICTENTITY *copyhashTableDict = hashTableDict[i];
                while (copyhashTableDict != NULL)
                {
                    printf("Word is %s\n", copyhashTableDict->word);
                    copyhashTableDict = copyhashTableDict->next;
                }
            }
        }
    }
}

// checking that word in dictionary for availability
bool check(char *word)
{
    if (quantityWords > 0)
    {
        int innerHash = 0;
        int checkHashWord = myHashFunction(word, &innerHash);
        printf("***********\n");
        printf("*%s* for check, hash is %i\n", word, checkHashWord);
        printf("quantityWords %i\n", quantityWords);
        // create copy of ptr needed index LL
        DICTENTITY *copyhashTableDict = hashTableDict[checkHashWord];
        if (copyhashTableDict != NULL)
        {
            printf("not null \n");
            while (copyhashTableDict != NULL)
            {
                if ((copyhashTableDict->hash == innerHash)
                    && (strcasecmp(copyhashTableDict->word, word) == 0))
                {
                    return true;
                }
                copyhashTableDict = copyhashTableDict->next;
            }
        }
    }
    return false;
}

// myHashFunction
int myHashFunction(char *word, int *fullHash)
{
    int hashKey = 0, koeff = 0;
//    printf("START HESHING ************* \n");
//    printf("Word for hashing right now is %s \n", word);

    for (int i = 0; i < strlen(word); i++)
    {
        hashKey = hashKey + toupper(word[i]);
        koeff++;
//        printf("hashKey: %i, ASCII: %i \n", hashKey, toupper(word[i]));
    }
    *fullHash = hashKey + (int) word[0] - koeff;
    hashKey = (hashKey + (word[0] - koeff)) % 26;
//    printf("hashKey: %i\n", hashKey);
//    printf("END HESHING ************* \n");

    return hashKey;
}
