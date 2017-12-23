/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

struct dictEntity
{
    char word[LENGTH+1];
    struct dictEntity *next;
};

typedef struct dictEntity DICTENTITY;
unsigned int sizeOfDictionary = 0;

DICTENTITY *createNewEntity();
void printDictionary();

DICTENTITY *dictionaryLinkList = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //printf("you are in check '%s' \n", word);
    if(dictionaryLinkList != NULL)
    {
        DICTENTITY *iterator = dictionaryLinkList->next;
        while(iterator != NULL)
        {
            if(strcasecmp(iterator->word, word) == 0) //it is doing: compare two strings ignoring cases
            {
                return true;
            }
            iterator = iterator->next;
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
        sizeOfDictionary = 0;
        dictionaryLinkList = createNewEntity();
        if(dictionaryLinkList)
        {
            DICTENTITY *lastNode = dictionaryLinkList;

            char everyWord[LENGTH + 1];
            result = true;
            while(fscanf(dictFile, "%s", everyWord) != EOF)
            {
                DICTENTITY *newNextNode = createNewEntity();
                if(newNextNode == NULL)
                {
                    result = false;
                    break;
                }
                sizeOfDictionary++;
                strcpy(newNextNode->word, everyWord);
                lastNode->next = newNextNode;
                lastNode = newNextNode;
            }
        }
        fclose(dictFile);
    }
    if(!result)
    {
        unload();
    }

    //printDictionary();
    return result;
}

void printDictionary()
{
    DICTENTITY* firstWord = dictionaryLinkList->next; //print without first item (zero value)

    while(firstWord != NULL)
    {
        printf("Word is %s\n", firstWord->word);
        firstWord = firstWord->next;
    }

    /*
    while(dictionaryLinkList != NULL) //print all
    {
        printf("Word is %s\n", dictionaryLinkList->word);
        dictionaryLinkList = dictionaryLinkList->next;
    }
*/

}


DICTENTITY *createNewEntity()
{
    DICTENTITY *result = malloc(sizeof(DICTENTITY));
    if(result == NULL)
    {
        return result;
    }

    memset(result, 0, sizeof(DICTENTITY)); // just one instead of two lines

    //memset(result->word, 0, sizeof(result->word));
    //result->next = NULL;

    return result;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(dictionaryLinkList != NULL)
    {
        return sizeOfDictionary;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if(dictionaryLinkList != NULL)
    {
        DICTENTITY *copyDictionaryLinkList = dictionaryLinkList;
        while(copyDictionaryLinkList != NULL)
        {
            DICTENTITY *middleNode = copyDictionaryLinkList->next;
            //printf("Delete word %s\n", copyDictionaryLinkList->word);
            free(copyDictionaryLinkList);
            copyDictionaryLinkList = middleNode;
        }
        dictionaryLinkList = NULL; //
        sizeOfDictionary = 0;
        return true;
    }
    else
    {
        return false;
    }
}
