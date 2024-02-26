
#ifndef OBJFILE_READER_PPM_H
#define OBJFILE_READER_PPM_H

#include <stdlib.h>

struct ppm {
    int width;
    int height;
    int *R;
    int *G;
    int *B;
    char *type;
    unsigned int size;
    int max_value;
};

struct ppm *set_ppm(int *ppm_content, int size_of_ppm);

struct ppm *read_ppm_file(const char *python_file, const char *python_function, const char *ppm_file);

void print_ppm_content(const struct ppm *ppm);

void print_ppm_content2(const struct ppm *ppm);

void free_ppm(struct ppm *ppm);

#endif 
