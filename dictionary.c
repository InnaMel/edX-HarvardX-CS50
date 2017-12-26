/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"
#define ALPHABET 26


struct dictEntity
{
    int hash;
    char word[LENGTH+1];
    struct dictEntity *next;
};

typedef struct dictEntity DICTENTITY;
DICTENTITY* hashTableDict[ALPHABET]; // my hash table (array of link list) for hashing dictionary массив 26 элементов

unsigned int sizeOfDictionary = 0;

DICTENTITY *createNewEntity();
void printDictionary();

int myHashFunction(const char *word, int *fullHash);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    if(sizeOfDictionary > 0)
    {
        int innerHash = 0;
        int checkHashWord = myHashFunction(word, &innerHash);
        // create copy of ptr needed index LL
        DICTENTITY* copyhashTableDict = hashTableDict[checkHashWord];
        if(copyhashTableDict != NULL)
        {
            while(copyhashTableDict != NULL)
            {
                if((copyhashTableDict->hash == innerHash) && (strcasecmp(copyhashTableDict->word, word) == 0))
                {
                    return true;
                }
                copyhashTableDict = copyhashTableDict->next;
            }
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    bool result = false;
    FILE * dictFile = fopen(dictionary, "r");
    if(dictFile)
    {
        memset(hashTableDict, 0, ALPHABET * sizeof(DICTENTITY*));
        char everyWord[45];
        result = true;

        while(fscanf(dictFile, "%s", everyWord) != EOF)
        {
            int hashStruct = 0;
            int currentHash = myHashFunction(everyWord, &hashStruct);
            DICTENTITY *newNextNode = createNewEntity();
            if(newNextNode == NULL)
            {
                result = false;
                unload();
                break;
            }

            //fill new node
            strcpy(newNextNode->word, everyWord);
            newNextNode->hash = hashStruct;
            sizeOfDictionary++;

            //swap
            newNextNode->next = hashTableDict[currentHash];
            hashTableDict[currentHash] = newNextNode;
        }
        fclose(dictFile);
    }
    if(!result)
    {
        unload();
    }

    return result;
}

// print
void printDictionary()
{
    printf("enter in print*************** \n");
    if(sizeOfDictionary > 0)
    {
        // create copy of ptr needed index LL
        for(int i = 0; i < ALPHABET; i++)
        {
            if(hashTableDict[i] != NULL)
            {
                DICTENTITY* copyhashTableDict = hashTableDict[i];
                while(copyhashTableDict != NULL)
                {
                    printf("Word is %s\n", copyhashTableDict->word);
                    copyhashTableDict = copyhashTableDict->next;
                }
            }
        }
    }
}


// Creating new node. Ask memory from mamloc.
DICTENTITY *createNewEntity()
{
    DICTENTITY *result = malloc(sizeof(DICTENTITY));
    if(result == NULL)
    {
        return result;
    }

    memset(result, 0, sizeof(DICTENTITY)); // zero pointers

    return result;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return sizeOfDictionary;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
// unload
bool unload(void)
{
    if(sizeOfDictionary > 0)
    {
        for(int i = 0; i < ALPHABET; i++)
        {
            DICTENTITY* copyhashTableDict = hashTableDict[i];
            while(copyhashTableDict != NULL)
            {
                DICTENTITY* next = copyhashTableDict->next; // create new entity for deleting step by step
                free(copyhashTableDict);
                copyhashTableDict = next;
            }
        }
        sizeOfDictionary = 0;
        return true;
    }
    else
    {
        return false;
    }
}


// myHashFunction
int myHashFunction(const char *word, int *fullHash)
{
    int hashKey = 0, koeff = 1;

    for (int i = 0; i < strlen(word); i++)
    {
        hashKey = hashKey + toupper(word[i]) * koeff;
        koeff++;
    }
    *fullHash = hashKey;
    hashKey = *fullHash % 26;

    return hashKey;
}

int myHashFunctionOLD(const char *word, int *fullHash)
{
    int hashKey = 0, koeff = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashKey = hashKey + toupper(word[i]);
        koeff++;
    }
    *fullHash = hashKey + (int)word[0] - koeff;
    hashKey = (hashKey + (word[0] - koeff)) % 26;

    return hashKey;
}
