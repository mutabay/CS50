#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cs50.h>
#include <ctype.h>


#define ALPHABET_LENGTH 26

int main(int argc, char * argv[])
{
    if(argc != 2 )
    {
        printf("%s key\n",argv[0]);
        return 1;
    }
    int i;
    for(i = 0; i <  strlen(argv[1]) ; i++)
    {
        if( ! isdigit(argv[1][i]) )
        {
            printf("%s key\n",argv[0]);
            return 1;
        }
    }

    //Firstly converting argv[1] to the integer and if this integer is digit then it is integer at the ASCII table.
    int key = atoi(argv[1]);

    char * plainText = get_string("Please enter the plain message\n");
    printf("plaintext:  %s\n",plainText);
    int textSize = strlen(plainText);

    for(i = 0 ; i <  textSize ; i++)
    {
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


    return 0;
}
