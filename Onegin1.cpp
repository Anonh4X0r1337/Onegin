#include "TXLib.h"
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------

void Swap (char** str1, char** str2);

int StringCompare (char* s1, char* s2);

void Sort (char** text, size_t n);

void Print (char** text, size_t n);

//-----------------------------------------------------------------------------


int main()
{

    const char* ptr = "OneginFile.txt";
    struct stat buf;
    stat (ptr, &buf);
    int file_size = buf.st_size; // получение размера файла

    FILE* fp = fopen ("OneginFile.txt", "rb");
    char* data = (char*)calloc(file_size, sizeof(char));
    fread (data, sizeof(char*), file_size, fp);  //открытие файла и заполения массива данными

    size_t n = 0;  //получение кол-ва строк
    for (int i = 0; i < file_size; i++)
    {
        if (data[i] == '\r')
        {
            i += 2;
            n++;
            continue;
        }
    }

    char** text = (char**)calloc(n, sizeof(char*)); // создание массива указателей (строк)
    text[0] = &data[0];
    int counter = 1; //заполнение массива указателями на строки
    for (int i = 0; i < file_size; i++)
    {
        if (data[i] == '\r')
        {
            data[i] = '\0';
            data[i+1] = '\0';
            text[counter] = &data[i+2];
            counter++;
            i += 2;
            continue;
        }
    }
    Print (text, n);
    putchar('\n');

    Sort (text, n);
    Print (text, n);

    free(data);
    free(text);

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

void Swap (char** str1, char** str2)
{
    char* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

//-----------------------------------------------------------------------------

void Sort (char** text, size_t n)
{
    for (size_t i = 0; i < n-1; i++)
    {
        for (size_t j = 0; j < n-1; j++)
        {
            if (StringCompare (text[j], text[j+1]) > 0)
            {
                Swap (&text[j], &text[j+1]);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Print (char** text, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {

        printf ("%s ", text[i]);

        printf ("\n");
    }
}

//-----------------------------------------------------------------------------


/*Выделяем память саlloc-ом или создаем структуру -> указатель на структуру -> stat*/



 /*size_t n = 0;
    for (int i = 0; i < file_size; i++)
    {
        if (data[i] == '\r')
        {
            i += 2;
            n++;
            continue;
        }
    }

    char** text = (char**)calloc(n, sizeof(char*));
    text[0] = data;
    size_t counter = 0;
    for (int i = 0; i < file_size; i++)
    {
        if (data[i] == '\r')
        {
            i += 2;
            text[counter] = (data + i);
            counter++;
            continue;
        }
    }   */

    /*Sort (text, n);
    Print (text, n);

    free(data); */
    /*FILE* fp = fopen ("OneginFile.txt", "rb");
    char* data = (char*)calloc(file_size, sizeof(char));
    fread (data, sizeof(char*), file_size, fp);
    for (int i = 0; i < file_size; i++)
    {
        if (data [i] !='\n')
        {
            putc(data[i], stdout);
        }
    }  */
