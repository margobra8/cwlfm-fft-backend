#include "ccsv.h"
#include <fftw3.h>
#define N 1024

int main()
{

    // file IO

    FILE *stream = fopen("data.csv", "r");
    FILE *out_data = fopen("out_data.csv", "w");

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
    // int ignore = 1;

    float input[3];
    int j = 0;

    fftwf_complex *in, *out;
    fftwf_plan p;

    in = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * N);
    out = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * N);

    // Measure optimal FFTW algorithm
    printf("Getting optimal FFTW algorithm...\n");
    p = fftwf_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_PATIENT);
    printf("Optimal algorithm found: %s\n", fftwf_sprint_plan(p));

    // Read values from file and store in memory
    while (fgets(line, 256, stream))
    {
        int i = 0;
        for (char *token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            input[i++] = atof(token);
        }

        //printf("%d: %f, %f\n", l++, input[0], input[1]);

        // Store input data in memory
        in[j][0] = input[0];
        in[j][1] = input[1];
        j++;

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
        printf("M[%d]: %f, %f\n", i, in[i][0], in[i][1]);
    }

    printf("FFT STEP\n");

    fftwf_execute(p);

    printf("FFT MEMORY\n");

    // check prints of floats in mem
    for (int k = 0; k < 1024; k++)
    {
        printf("M[%d]: %f, %f\n", k, out[k][0], out[k][1]);
        fprintf(out_data, "%f,%f\n", out[k][0], out[k][1]);
    }

    fftwf_destroy_plan(p);
    fftwf_free(in);
    fftwf_free(out);
    fclose(stream);
    fclose(out_data);
}