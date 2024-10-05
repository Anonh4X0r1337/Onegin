#include "TXLib.h"
#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//-----------------------------------------------------------------------------

void Swap (char** str1, char** str2);

int StringCompare (char* s1, char* s2);

void Sort (char** text, size_t n);

void Print (char** text, size_t n);

size_t SizeOfFile (const char* ptr);

void FillData (char* data, size_t* nLines, size_t* nChars, FILE* fp);

void FreeArrayOfPointers (char**, size_t);

void PrintData (char* data, size_t nChars);

//-----------------------------------------------------------------------------


int main()
{

    const char* ptr = "OneginFile.txt";
    size_t file_size = SizeOfFile (ptr);

    printf ("%u - file_size (with \\r and \\n)\n\n", file_size);

    FILE* fp = fopen ("OneginFile.txt", "rb");

    char* data = (char*)calloc(file_size, sizeof(char));

    size_t nLines = 0;
    size_t nChars = 0;
    FillData (data, &nLines, &nChars, fp);
    assert (data != NULL);

    PrintData (data, nChars);

    char** text = (char**)calloc(nLines, sizeof(char*));


    printf("%d lines\n", nLines);

    text[0] = data;
    printf ("n[1]: %s %c", data, '\n');
    int counter = 1;
    for (size_t i = 1; i < nChars-1; i++)
    {
        if (data[i] == 0)
        {
            text[counter] = &data[i+1];

            printf("n[%d]: %s\n", counter+1, text[counter]);

            counter++;
        }
    }
    putchar ('\n');

    Sort (text, nLines);
    Print (text, nLines);

    free (data);
    FreeArrayOfPointers (text, nLines);

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
        }
    }
}

//-----------------------------------------------------------------------------

void Swap (char** str1, char** str2)
{
    char* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

//-----------------------------------------------------------------------------

void Sort (char** text, size_t nLines)
{
    for (size_t i = 0; i < nLines-1; i++)
    {
        for (size_t j = 0; j < nLines-1; j++)
        {
            if (StringCompare (text[j], text[j+1]) > 0)
            {
                Swap (&text[j], &text[j+1]);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Print (char** text, size_t nLines)
{
    for (size_t i = 0; i < nLines; i++)
    {
        printf ("%s\n", text[i]);
    }
}

//-----------------------------------------------------------------------------

size_t SizeOfFile (const char* ptr)
{
    assert (ptr != NULL);
    struct stat buf;
    stat (ptr, &buf);
    size_t file_size = buf.st_size;
    return file_size;
}

//-----------------------------------------------------------------------------

void FillData (char* data, size_t* nLines, size_t* nChars, FILE* fp)
{
    assert (data != NULL);
    assert (nLines != NULL);
    assert (nChars != NULL);
    assert (fp != NULL);

    for (char ch = 0; (ch = getc (fp)) != EOF; (*nChars)++)
    {
        if (ch == '\r')
        {
            (*nLines)++;
            printf ("  %u", *nChars);
            putchar ('\n');
            if ((ch == getc (fp)) == EOF)
            {
                return;
            }
            data[*nChars] = '\0';
        }
        else
        {
            putchar (ch);
            data[*nChars] = ch;
        }
    }
    putchar ('\n');
    realloc (data, (*nChars)*sizeof(char));
    printf ("%u chars in data\n", *nChars);
}

//-----------------------------------------------------------------------------

void FreeArrayOfPointers (char** arr, size_t size_arr)
{
    for (size_t i = 0; i <  size_arr; i++)
    {
        free(arr[i]);
    }
}

//-----------------------------------------------------------------------------

void PrintData (char* data, size_t nChars)
{
    for (size_t i = 0; i < nChars; i++)
    {
        if (data[i] == 0)
        {
            printf ("\\0\n");
            continue;
        }
        putchar (data[i]);
    }
    putchar ('\n');
}


