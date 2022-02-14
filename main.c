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
    char line[256];
    int l = 0;
    int ignore = 1;
    float input[3];

    float* res = (float*) pffft_aligned_malloc(sizeof(float) * 1024);
    float* imgs = (float*) pffft_aligned_malloc(sizeof(float) * 1024);

    while (fgets(line, 256, stream))
    {
        int i = 0;
        for (char *token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            input[i++] = atof(token);
        }

        *res = input[0];
        *imgs = input[1];

        res++;
        imgs++;

        printf("%d: %f, %f\n", l, input[0], input[1]);
        l++;

        // trigger detection
        // if (input[2] == 0 || ignore == 1)
        // {
        //     if (ignore = 1)
        //         ignore = 0;
            
        // }


    }
    printf("MEMORY\n");
    // check prints of floats in mem
    for (int i = 0; i < 1024; i++)
    {
        printf("%f, %f\n", res[i], imgs[i]);
    }
}