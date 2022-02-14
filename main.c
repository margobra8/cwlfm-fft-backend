#include "ccsv.h"
#include "pffft.h"

int main()
{

    //read csv file
    FILE *stream = fopen("data.csv", "r");
    if (stream == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    char line[2048];
    int ignore = 1;
    float input[3];

    reals = pffft_aligned_malloc(sizeof(float) * 2048);

    while (fgets(line, 2048, stream))
    {
        int i = 0;
        for (char *token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            input[i++] = atof(token);
        }

        if (input[2] == 0 || ignore == 1)
        {
            if (ignore = 1)
                ignore = 0;
            
        }
    }
}