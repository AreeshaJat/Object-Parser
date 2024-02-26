#include <stdio.h>
#include "wavefront.h"
#include "ppm.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./a1 python_file python_function obj_ppm_name\n");
        return 1;
    }
    const char *python_file = argv[1];
    const char *python_function = argv[2];

    const char *name = argv[3];
    char *obj_file = malloc((strlen(name) + 4) * sizeof(char));
    char *ppm_file = malloc((strlen(name) + 4) * sizeof(char));
    strcpy(obj_file, name);
    strcpy(ppm_file, name);
    strcat(obj_file, ".obj");
    strcat(ppm_file, ".ppm");

    struct wavefront *wavefront;
    struct ppm *ppm;
    wavefront = read_obj_file(obj_file);
    if (!wavefront) {
        printf("Could not parse obj file %s\n", obj_file);
        return 1;
    }

    ppm = read_ppm_file(python_file, python_function, ppm_file);
    if (!ppm) {
        printf("Could not parse ppm file %s\n", ppm_file);
        return 1;
    }

    printf("\n\n");
    print_wavefront_content2(wavefront);
    print_ppm_content2(ppm);

    free_wavefront(wavefront);
    free_ppm(ppm);
    return 0;
}
