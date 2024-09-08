#include "TXLib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------

void Swap (char* str1, char* str2);

int StringCompare (char* s1, char* s2);

void Sort (char* text, size_t n);

void Print (char* text, size_t n, size_t m);

//-----------------------------------------------------------------------------


int main()
{
    const size_t n = 7, m = 7;
    char text[n][m] = {
                      {"мой"},
                      {"когда"},
                      {"он"},
                      {"и"},
                      {"его"},
                      {"и"},
                      {"кот"}
                      };

    Sort (*text, n);
    Print (*text, n, m);



    return 0;
}

//-----------------------------------------------------------------------------

int StringCompare (char* s1, char* s2)
{
    int counter = 0;
    while (1)
    {
        if (*(s1 + counter) == 0 && *(s2 + counter) == 0)
        {
            return 0;
        }
        if (*(s1 + counter) != *(s2 + counter))
        {
            return ((int)*(s1 + counter) - (int)*(s2 + counter));
        }
        else
        {
            counter++;
            continue;
        }
    }
}

//-----------------------------------------------------------------------------

void Swap (char* str1, char* str2)
{
    printf ("%d", strlen(str1));
    char* temp = (char*)calloc((strlen(str1) + 1), sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

//-----------------------------------------------------------------------------

void Sort (char* text, size_t n)
{
    for (size_t i = 0; i < n-1; i++)
    {
        for (size_t j = 0; j < n-1; j++)
        {
            if (StringCompare (&text[j], &text[j+1]) > 0)
            {
                Swap (&text[j], &text[j+1]);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Print (char* text, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j != '\0'; j++)
        {
            printf ("%d ", *(text + i*m + j));
        }
        printf ("\n");
    }
}

//-----------------------------------------------------------------------------
