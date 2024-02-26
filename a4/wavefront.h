#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* indices in count array of struct wavefront */
#define V  0
#define VT 1
#define VN 2
#define F  3

/*
 * Structure Definitions
 */

/* face component */
struct facecomponent {
    /* indices are stored 1-based */
    unsigned int vi;  /* vertice index */
    unsigned int vti; /* vt index or 0 if missing */
    unsigned int vni; /* vn index or 0 if missing */
};

/* face */
struct face {
    struct facecomponent fc[4];   /* zero-based, last may be missing */
    unsigned char cnt; /* number of face components: 3 or 4 */
};

/* stores the whole file, once parsed correctly */
struct wavefront {
    char *g;    /* group name */
    char *o;    /* object name */
    double *v;  /* vertices */
    double *vt; /* vertices' texture coordinates */
    double *vn; /* vertex normals */
    struct face *f; /* faces */
    unsigned int count[4]; /* count for each of v, vt, vn and f */
};

/*
 * Functions
 */

/*
 * Parses wavefront objfile
 */
struct wavefront *read_obj_file(const char *filename);

/*
 * Frees wavefront structure
 */
void free_wavefront(struct wavefront *wavefront);

/*
 * Prints a valid wavefront structure
 */
void print_wavefront_content(struct wavefront *wavefront);

void print_wavefront_content2(struct wavefront *wavefront);

void read_comment_line(FILE *file);

char *read_group_or_object_name_line(FILE *file);

double *read_vertice_line(FILE *file);

double *read_vertice_texture_line(FILE *file);

double *read_vertex_normal_line(FILE *file);

int *read_face_line(FILE *file, int *array_size);

void add_vertice(struct wavefront *wavefront, const double *values);

void add_vertice_texture(struct wavefront *wavefront, const double *values);

void add_vertice_normal(struct wavefront *wavefront, const double *values);

void append_to_char_array(char *array, int array_size, int character);

int *append_to_int_array(int *array, const int size, const int character);

void add_face(struct wavefront *wavefront, const int *face_components, int face_components_size);

void reset_string_buffer(int *string_size, char **string_buffer);