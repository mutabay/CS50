#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Wrong usage : ImageFile\n");
        return 1;
    }
    char * cardName = argv[1];

    FILE * inptr = fopen(cardName, "r");
    if (! inptr)
    {
        fprintf(stderr, "%s file couldn't opened\n",cardName);
        return 2;
    }

    unsigned char buffer[BLOCK_SIZE];
    fread(buffer ,BLOCK_SIZE ,1 ,inptr);
    int filecount = 0;
    int jpegFound = 0;
    FILE * outptr = NULL;
    while (buffer != EOF)
    {
        //Controlling jpeg header.
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //close previous jpeg file
            if (jpegFound = 1)
            {
                fclose(outptr);
            }
            else
            {
                //jpeg discovered and now we can write it.
            }
            //create filename
            char jpegFileName[8];
            sprintf(jpegFileName,"%03d.img",filecount);

            //open new image file
            outptr = fopen(jpegFileName, "a");
            if (!outptr)
            {
                fprintf(stderr, "%s file couldn't opened\n",jpegFileName);
                return 3;
            }
            jpegFound++;
        }

        if (jpegFound == 1)
        {
            //write 512 bytes to file once we start finding jpegs.
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }

        fread(buffer ,BLOCK_SIZE ,1 ,inptr);

    }

    fclose(inptr);
    fclose(outptr);

}
