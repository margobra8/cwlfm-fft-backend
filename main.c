#include "ccsv.h"
#include "pffft.h"

int main()
{

    //read csv file
    FILE *stream = fopen("data.csv", "r");
    FILE *out_data =  fopen("out_data.csv", "w");
    if (stream == NULL)
    {
        printf("Error opening file 'data.csv'\n");
        return 1;
    }
    if (out_data == NULL)
    {
        printf("Error opening file 'out_data.csv'\n");
        return 1;
    }
    char line[256];
    int l = 0;
    int ignore = 1;
    float input[3];
    int ii = 0;
    int oi = 0;

    float *in = (float *)pffft_aligned_malloc(sizeof(float) * 1024 * 2);
    float *out = (float *)pffft_aligned_malloc(sizeof(float) * 1024 * 2);

    PFFFT_Setup *s = pffft_new_setup(1024, PFFFT_COMPLEX);

    while (fgets(line, 256, stream))
    {
        int i = 0;
        for (char *token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            input[i++] = atof(token);
        }

        in[ii] = input[0];
        in[ii+1] = input[1];
        ii++;

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
        printf("M[%d,%d]: %f, %f\n", i, i+1024, in[i], in[i+1]);
    }

    printf("FFT STEP\n");

    pffft_transform_ordered(s, in, out, NULL, PFFFT_FORWARD);

    printf("FFT MEMORY\n");
    
    // check prints of floats in mem
    for (int i = 0; i < 1024; i++)
    {
        printf("MFFT[%d,%d]: %f, %f\n", i, i+1, out[i], out[i+1]);
        fprintf(out_data, "%f,%f\n", out[i], out[i+1]);
    }

    pffft_destroy_setup(s);
    pffft_aligned_free(in);
    pffft_aligned_free(out);
    fclose(stream);
    fclose(out_data);
}