/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"


void swap(int *A, int *B);

/*bool search(int value, int values[], int n);
void sort(int values[], int n);

int main(void)
{
    return 0;
}*/

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    bool ifNum = false;
    if (n <= 0)
    {
    ifNum = false;
    }

if (n <= 3)
{
    for (int i = 0; i < n; i++)
    {
        if (value == values[i])
        ifNum = true;
    }
}

if (ifNum != true)
{
    int middle = n / 2;
    int i = 0;
    if ((value > values[middle]) && (value < values[middle + 1]))
    {
        ifNum = false;
    }
    else
    {
        while ((middle - i) >= 2)
        {
            if (value < values[middle])
            {
                n = middle;
                middle = i + ((middle - i) / 2);
            }
            else
            {
                i = middle;
                middle = ((n - middle) / 2) + middle;
            }
        }
        n = middle;
        for (int l = i; l <= n; l++)
        {
            if (value == values[l])
            ifNum = true;
        }
    }
}
    return ifNum;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (values[i+1] < values[i])
        {
            swap(&values[i+1], &values[i]);
            for (int j = i - 1; j >= 0; j--)
            {
                if (values[i] < values[j])
                {
                    swap(&values[i], &values[j]);
                    i--;
                }
                else
                break;
            }
        }
    }
    return;
}

void swap(int *A, int *B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}