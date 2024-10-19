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

void FillText (char** text, char* data, size_t nChars);

void PrintData (char* data, size_t nChars);

//-----------------------------------------------------------------------------


int main()
{
    const char* filename = "OneginFile.txt";
    size_t file_size = SizeOfFile (filename);

    printf ("%zu - file_size (with \\r and \\n)\n\n", file_size);

    FILE* fp = fopen ("OneginFile.txt", "rb");

    char* data = (char*)calloc(file_size, sizeof(char)); // FIXME check
    printf ("data - %p\n", data);

    size_t nLines = 0;
    size_t nChars = 0;
    printf ("nChars - %p\n", &nChars);
    FillData (data, &nLines, &nChars, fp); // заполнение массива символов data
    //printf ("data после заполения символами - %p\n", data);
    PrintData (data, nChars);

    printf("%zu lines\n", nLines);

    char** text = (char**)calloc(nLines, sizeof(char*)); // FIXME check
    FillText (text, data, nChars); // заполнение массива строк text

    Sort (text, nLines);
    Print (text, nLines);

    free (data);
    free (text);

    return 0;
}

//-----------------------------------------------------------------------------

int StringCompare (char* s1, char* s2)
{
    int res = 0;
    for (int i = 0; s1[i] && s2[i]; i++)
    {
        if ((res = s1[i] - s2[i]) != 0)
        {
            break; // FIXME
        }
    }
    return res;
}

// abcdef0
// abc0

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
    stat (ptr, &buf); // FIXME check error
    size_t file_size = (size_t)buf.st_size;
    return file_size;
}

//-----------------------------------------------------------------------------

void FillText (char** text, char* data, size_t nChars)
{
    text[0] = data;
    fprintf (stderr, "text[1]: %s \n", *text);
    size_t counter = 1;
    for (size_t i = 1; i < nChars-1; i++)
    {
        if (data[i] == 0)
        {
            text[counter] = &data[i+1];
            printf ("text[%zu]: %s\n", counter+1, text[counter]);
            counter++;
        }
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
//-------------------------------------------------------------------------------

void FillData (char* data, size_t* nLines, size_t* nChars, FILE* fp)
{
    printf ("nChars - %p\n", &nChars);

    int ch = 0;

    bool what_mode_is = false; // определение типа файла
    while ((ch = getc (fp)) != '\n')
    {
        if (ch == '\r')
        {
            what_mode_is = true;
            data[*nChars] = '\0';
            (*nChars)++;
            getc (fp); // считываем \n
            break;
        }
        data[*nChars] = (char)ch;
        (*nChars)++;
    }
    (*nLines)++;
    printf("1 line: %zu\n", *nChars);

    if (what_mode_is) // заполнение data, если есть \r
    {
        for (; (ch = getc (fp)) != EOF; (*nLines)++)
        {
            for (; (ch = getc (fp)) != '\r'; (*nChars)++)
            {
                data[*nChars] = (char)ch;
            }

            data[*nChars] = '\0'; // сейчас ch = '\r'
            (*nChars)++;
            printf("%zu line: %zu\n", (*nLines)+1, *nChars);

            getc (fp); // считываем \n
        }
    }
    else // заполнение data, если есть только \n
    {
        data[*nChars] = '\0';
        for (; (ch = getc (fp)) != EOF; (*nLines)++)
        {
            for (; ch != '\n'; (*nChars)++)
            {
                data[*nChars] = (char)ch;
            }
            data[*nChars] = '\0';
            (*nChars)++;
        }
    }
}
