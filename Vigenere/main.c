#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cs50.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26
int ConvertTextToKey(char c)
{   int key = 0;
    if( 'A' <= c && c <= 'Z' )
    {
        key = c - 'A';
    }
    else if( 'a' <= c && c <= 'z' )
    {
        key = c - 'a';
    }
    return key;
}

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s keyword\n",argv[0]);
        return 1;
    }

    int i;
    for(i = 0; i <  strlen(argv[1]) ; i++)
    {
        if(  isdigit(argv[1][i]) )
        {
            printf("Usage: %s keyword\n",argv[0]);
            return 1;
        }
    }

    string plainText = get_string("Please enter the plain message\n");
    printf("plaintext:  %s\n",plainText);
    int textSize = strlen(plainText);
    int keywordSize = strlen(argv[1]);
    string keyword = argv[1];
    for(i = 0 ; i <  textSize ; i++)
    {
        int key = ConvertTextToKey(argv[1][i % keywordSize]);
        //UPPERCASE
        if( 'A' <= plainText[i] && plainText[i] <= 'Z' )
        {
            plainText[i] = plainText[i] - 'A';
            plainText[i] = (plainText[i] + key) % ALPHABET_LENGTH;
            plainText[i] = plainText[i] + 'A';
        }
        else if( 'a' <= plainText[i] && plainText[i] <= 'z' )
        {
            plainText[i] = plainText[i] - 'a';
            plainText[i] = (plainText[i] + key) % ALPHABET_LENGTH;
            plainText[i] = plainText[i] + 'a';
        }

    }
    printf("ciphertext: %s\n",plainText);



}
