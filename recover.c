// get jpgs from recover file
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int nmOfArguments, string argValues[])
{
    printf("%i %s\n", nmOfArguments, argValues[0]);
    // check to mmake sure we have argurments
    if (nmOfArguments == 2)
    {
        char *file = argValues[1];
        FILE *card = fopen(file, "r");
        if (!card)
        {
            printf("No file or nothing in file \n");
            fclose(card);
            return 1;
        }
        // define buffer
        unsigned char buffer[512];
        // keep count
        int imgcount = 0;
        FILE *jpg = NULL;

        // printf("above char * line 28\n");
        char filename[8];
        while (fread(buffer, 512, 1, card) == 1)
        {
            // printf("reading buffer  line 32\n");
            // is this a jpg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // printf("found a jpg line 36\n");

                // increment the filename to 3 characters using imgcount
                sprintf(filename, "%03d.jpg", imgcount);
                // open a new jpg file
                jpg = fopen(filename, "w");
                // check that there really is a jpg file in the buffer
                if (jpg == NULL)
                {
                    printf("failed to open file");
                }

                // write the contents of the buffer into a file
                fwrite(buffer, 512, 1, jpg);
                // use printf to check the names of the image files
                // printf("filename %3s.jpg\n", filename);
                // printf("buffer 0, 1, 2, %i %i %i\n", buffer[0], buffer[1], buffer[3]);

                imgcount++;
            }
            // if the beginning files are junk and don't have jpg files in them,
            else if (jpg != NULL)
            {
                fwrite(buffer, 512, 1, jpg);
            }
        }
        // printf("Total number of JPG images in file %i\n", imgcount);
        fclose(card);
        return 0;
    }
    else
    {
        printf("Usage: ./getJpg filename \n");
        return 1;
    }
}