#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int check_jpg(BYTE bf[]);
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    char *infile = argv[1];
    char outfile[7] = {0};
    
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Can't open %s.\n", infile);
        return 1;
    }
    
    BYTE bf[512] = {0};
    int n = 0;
    int flag = 0;
    FILE *outptr = NULL;
    while (fread(bf, sizeof(BYTE), 512, inptr))
    {
        if (check_jpg(bf) && flag == 1)
        {
            fwrite(bf, sizeof(BYTE), 512, outptr);
        }
        else if (!check_jpg(bf))
        {
            flag = 1;
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(outfile, "%03i.jpg", n);
            n++;
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Can't create %s.\n", outfile);
                return 1;
            }
            
            fwrite(bf, sizeof(BYTE), 512, outptr);
        }
        
    }
    
    fclose(outptr);
    fclose(inptr);
    return 0;
    
}

int check_jpg(BYTE bf[])
{
    if (bf[0] == 0xff && bf[1] == 0xd8 && bf[2] == 0xff && 
        bf[3] >= 0xe0 && bf[3] <= 0xef)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}