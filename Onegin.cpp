#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/*struct file
{


struct string
{
    char* s_begin;
    char* s_end;
};*/

//-----------------------------------------------------------------------------

void Swap (char** str1, char** str2);

int StringCompare (char* s1, char* s2);

void Sort (char** text, size_t n);

void Print (char** text, size_t n);

size_t SizeOfFile (const char* ptr);

void FillText (char** text, char* data, bool what_mode_is, size_t file_size);

void PrintData (char* data, size_t nChars);

//-----------------------------------------------------------------------------


int main()
{
    const char* filename = "OneginFile.txt";
    size_t file_size = SizeOfFile (filename);

    printf ("%zu - file_size (with \\r and \\n)\n\n", file_size);

    FILE* fp = fopen ("OneginFile.txt", "rb");
    if (fp == NULL)
    {
        printf ("Не удаётся открыть файл");
        exit (EXIT_FAILURE);
    }

    char* data = (char*)calloc(file_size, sizeof(char)); // FIXME check
    printf ("data - %p\n", data);

    if (fread (data, sizeof(char), file_size, fp) < file_size)
    {
        printf ("Ошибка");
        return 0;
    }

    size_t nLines = 0;
    bool what_mode_is = false; // определение типа файла
    for (size_t i = 0; data[i] != '\n'; i++)
    {
        if (data[i] == '\r')
        {
            what_mode_is = true;
            data[i] = '\0';
            i++;
            break;
        }
    }
    nLines++;

    if (what_mode_is)
    {
        for (size_t i = 0; i < file_size; i++)
        {
        if (data[i] == '\r')
        {
            data[i] = '\0';
            i++;
            nLines++;
        }
        }
    }
    else
    {
        for (size_t i = 0; i < file_size; i++)
        {
        if (data[i] == '\n')
        {
            data[i] = '\0';
            nLines++;
        }
        }
    }

    //printf ("data после заполения символами - %p\n", data);
    PrintData (data, file_size);

    char** text = (char**)calloc(nLines, sizeof(char*)); // FIXME check
    FillText (text, data, what_mode_is, file_size); // заполнение массива строк text

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
        res = s1[i] - s2[i];
        if (res != 0)
        {
            break;
        }
    }
    return res;
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
/*i;
2i+1;
2i+2;*/

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

void FillText (char** text, char* data, bool what_mode_is, size_t file_size)
{
    text[0] = data;
    printf ("text[1]: %s \n", *text);
    size_t counter = 1;
    if (what_mode_is)
    {
        for (size_t i = 1; i < file_size-2; i++)
        {
            if (data[i] == '\0')
            {

                text[counter] = &data[i+2];
                printf ("text[%zu]: %s\n", counter+1, text[counter]);
                counter++;
            }
        }
    }
    else
    {
        for (size_t i = 1; i < file_size-1; i++)
        {
            if (data[i] == '\0')
            {
                text[counter] = &data[i+1];
                printf ("text[%zu]: %s\n", counter+1, text[counter]);
                counter++;
            }
        }
    }
    putchar ('\n');
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
