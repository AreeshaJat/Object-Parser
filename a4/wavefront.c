
#include "wavefront.h"

/*
 * prints a valid wavefront structure
 */
void print_wavefront_content(struct wavefront *wavefront)
{

    if (wavefront->g)
        printf("Group: %s\n", wavefront->g);
    if (wavefront->o)
        printf("Object: %s\n", wavefront->o);

    unsigned int face_index;
    for (face_index = 0; face_index < wavefront->count[F]; face_index++)
    {
        struct face *face_i = &wavefront->f[face_index];
        unsigned int component_index;

        /* print vertices for this face_i */
        printf("f%u v", face_index + 1);
        for (component_index = 0; component_index < face_i->cnt; component_index++)
        {
            struct facecomponent *fc = &face_i->fc[component_index];
            unsigned int vi = fc->vi - 1;
            printf("    %g %g %g", wavefront->v[3 * vi], wavefront->v[3 * vi + 1], wavefront->v[3 * vi + 2]);
        }
        printf("\n");

        /* print vertices textures for this face_i */
        if (face_i->fc[0].vti || face_i->fc[1].vti || face_i->fc[2].vti || face_i->fc[3].vti)
        {
            printf("f%u vt", face_index + 1);
            for (component_index = 0; component_index < face_i->cnt; component_index++)
            {
                struct facecomponent *fc = &face_i->fc[component_index];
                if (fc->vti)
                {
                    unsigned int vti = fc->vti - 1;
                    printf("    %g %g", wavefront->vt[2 * vti], wavefront->vt[2 * vti + 1]);
                }
            }
            printf("\n");
        }

        /* print vertex normals for this face_i */
        if (face_i->fc[0].vni || face_i->fc[1].vni || face_i->fc[2].vni || face_i->fc[3].vni)
        {
            printf("f%u vn", face_index + 1);
            for (component_index = 0; component_index < face_i->cnt; component_index++)
            {
                struct facecomponent *fc = &face_i->fc[component_index];
                if (fc->vni)
                {
                    unsigned int vni = fc->vni - 1;
                    printf("    %g %g %g", wavefront->vn[3 * vni], wavefront->vn[3 * vni + 1],
                           wavefront->vn[3 * vni + 2]);
                }
            }
            printf("\n");
        }
    }
}

/*
 * prints a valid wavefront structure for WebGL module
 */
void print_wavefront_content2(struct wavefront *wavefront)
{
    printf("OBJ\n");

    int offset = 0;
    
    unsigned int vi_component_index = 0;
    unsigned int vti_component_index = 0;
    unsigned int vni_component_index = 0;
    for (unsigned int face_index = 0; face_index < wavefront->count[F]; face_index++)
    {
        struct face *face_i = &wavefront->f[face_index];

        for (int group = 0; group < 3; group++)
        {
            /* print vertices for this face_i */
            if (vi_component_index < face_i->cnt)
            {
                struct facecomponent *fc = &face_i->fc[vi_component_index];
                unsigned int vi = fc->vi - 1;
                printf("%u,%g,%g,%g", vi, wavefront->v[3 * vi], wavefront->v[3 * vi + 1], wavefront->v[3 * vi + 2]);
                vi_component_index = (vi_component_index + 1) % face_i->cnt;
            }

            /* print vertices textures for this face_i */
            if (face_i->fc[0].vti || face_i->fc[1].vti || face_i->fc[2].vti || face_i->fc[3].vti)
            {
                if (vti_component_index < face_i->cnt)
                {
                    struct facecomponent *fc = &face_i->fc[vti_component_index];
                    if (fc->vti)
                    {
                        unsigned int vti = fc->vti - 1;
                        printf(",%g,%g", wavefront->vt[2 * vti], wavefront->vt[2 * vti + 1]);
                    }
                    vti_component_index = (vti_component_index + 1) % face_i->cnt;
                }
            }

            /* print vertex normals for this face_i */
            if (face_i->fc[0].vni || face_i->fc[1].vni || face_i->fc[2].vni || face_i->fc[3].vni)
            {
                if (vni_component_index < face_i->cnt)
                {
                    struct facecomponent *fc = &face_i->fc[vni_component_index];
                    if (fc->vni)
                    {
                        unsigned int vni = fc->vni - 1;
                        printf(",%g,%g,%g", wavefront->vn[3 * vni], wavefront->vn[3 * vni + 1],
                               wavefront->vn[3 * vni + 2]);
                    }
                    vni_component_index = (vni_component_index + 1) % face_i->cnt;
                }
            }
            printf("\n");
        }
    }
}

/*
 * deallocate content of wavefront struct from memory.
 * */
void free_wavefront(struct wavefront *wavefront)
{
    if (wavefront->g)
        free(wavefront->g);
    if (wavefront->o)
        free(wavefront->o);
    if (wavefront->v)
        free(wavefront->v);
    if (wavefront->vt)
        free(wavefront->vt);
    if (wavefront->vn)
        free(wavefront->vn);
    free(wavefront->f);
    free(wavefront);
}

/*
 * General line reading function.
 * read a character from file, then starts parsing according to read character.
 * */
void read_line(struct wavefront *wavefront, FILE *file)
{
    char current_char = (char)getc(file);

    if (current_char == '#')
    {
        read_comment_line(file);
    }
    else if (current_char == 'g')
    {
        char *group_name = read_group_or_object_name_line(file);
        wavefront->g = group_name;
    }
    else if (current_char == 'o')
    {
        char *object_name = read_group_or_object_name_line(file);
        wavefront->o = object_name;
    }
    else if (current_char == 'v')
    {
        current_char = (char)getc(file);

        if (current_char == ' ')
        {
            double *vertice_values = read_vertice_line(file);
            add_vertice(wavefront, vertice_values);
        }
        else if (current_char == 't')
        {
            double *vertice_texture_values = read_vertice_texture_line(file);
            add_vertice_texture(wavefront, vertice_texture_values);
        }
        else if (current_char == 'n')
        {
            double *vertice_normals_values = read_vertex_normal_line(file);
            add_vertice_normal(wavefront, vertice_normals_values);
        }
    }
    else if (current_char == 'f')
    {
        int face_components_size = 0;

        int *face_components = read_face_line(file, &face_components_size);
        add_face(wavefront, face_components, face_components_size);
    }
    else if (current_char == EOF)
    {
        return;
    }

    read_line(wavefront, file);
}

/*
 * function that initialize processes.
 * */
struct wavefront *read_obj_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening %s\n", filename);
        return NULL;
    }

    /* Initializer allocation of wavefront */
    struct wavefront *wavefront = NULL;
    wavefront = calloc(1, sizeof(struct wavefront));

    read_line(wavefront, file);

    fclose(file);
    return wavefront;
}

/*
 * read and write face components into the wavefront structure.
 * */
void add_face(struct wavefront *wavefront, const int *face_components, const int face_components_size)
{
    struct face *temp_buffer_for_face = NULL;

    /*
     * incremented by 512 for signal faults
     * */
    if (wavefront->count[F] % 512 == 0)
    {
        temp_buffer_for_face = calloc((wavefront->count[F] + 512), sizeof(struct face));

        /*
         * deep copy from wavefront to temp buffer for realloc errors
         * */
        int i, j;
        for (i = 0; i < wavefront->count[F]; i++)
        {
            for (j = 0; j < wavefront->f[i].cnt; ++j)
            {
                temp_buffer_for_face[i].fc[j].vi = wavefront->f[i].fc[j].vi;
                temp_buffer_for_face[i].fc[j].vti = wavefront->f[i].fc[j].vti;
                temp_buffer_for_face[i].fc[j].vni = wavefront->f[i].fc[j].vni;
            }
            temp_buffer_for_face[i].cnt = wavefront->f[i].cnt;
        }
        /* deallocation for memory leaks */
        free(wavefront->f);
        wavefront->f = temp_buffer_for_face;
    }

    /*
     * transfers the face components read from the file to the wavefront structure.
     * set 0 for exception case
     * */
    unsigned long size = wavefront->count[F];
    wavefront->f[size].cnt = face_components_size / 3;
    int i, j;
    for (i = 0, j = 0; i < face_components_size; i = i + 3, j++)
    {
        wavefront->f[size].fc[j].vi = face_components[i];
        wavefront->f[size].fc[j].vti = face_components[i + 1] == 0 ? 0 : face_components[i + 1];
        wavefront->f[size].fc[j].vni = face_components[i + 2] == 0 ? 0 : face_components[i + 2];
    }
    wavefront->count[F]++;
}

/*
 * set the vertice normal values read from file to wavefront structure.
 * */
void add_vertice_normal(struct wavefront *wavefront, const double *values)
{
    wavefront->count[VN]++;
    wavefront->vn = realloc(wavefront->vn, 3 * wavefront->count[VN] * sizeof(double));
    wavefront->vn[3 * (wavefront->count[VN] - 1)] = values[0];
    wavefront->vn[3 * (wavefront->count[VN] - 1) + 1] = values[1];
    wavefront->vn[3 * (wavefront->count[VN] - 1) + 2] = values[2];
}

/*
 * set the vertice texture values read from file to wavefront structure.
 * */
void add_vertice_texture(struct wavefront *wavefront, const double *values)
{
    wavefront->count[VT]++;
    wavefront->vt = realloc(wavefront->vt, 2 * wavefront->count[VT] * sizeof(double));
    wavefront->vt[2 * (wavefront->count[VT] - 1)] = values[0];
    wavefront->vt[2 * (wavefront->count[VT] - 1) + 1] = values[1];
}

/*
 * set the vertice values read from file to wavefront structure.
 * */
void add_vertice(struct wavefront *wavefront, const double *values)
{
    wavefront->count[V]++;
    wavefront->v = realloc(wavefront->v, 3 * wavefront->count[V] * sizeof(double));

    wavefront->v[3 * (wavefront->count[V] - 1)] = values[0];
    wavefront->v[3 * (wavefront->count[V] - 1) + 1] = values[1];
    wavefront->v[3 * (wavefront->count[V] - 1) + 2] = values[2];
}

/*
 * read and parse face line from file
 * */
void parse_f_line(FILE *file, int *array_size, int *string_size, int slash_number, char **string_buffer,
                  int **face_components)
{
    char read_character = (char)getc(file);

    /* It was chosen as unimportant because the number of spaces is variable. */
    if (read_character != ' ')
    {

        /* When read the slash character (/), means the component has been read.   */
        if (read_character == '/')
        {

            /*
             * in case that not exist vt values in file.
             * */
            if ((*string_buffer)[0] == (char)0)
            {
                (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
            }
            else
                (*face_components) = append_to_int_array((*face_components), (*array_size), atoi((*string_buffer)));

            slash_number++;
            (*array_size)++;
            reset_string_buffer(string_size, string_buffer);

            /* continue */
            parse_f_line(file, array_size, string_size, slash_number, string_buffer, face_components);
            return;
        }
        else if (read_character == '\n')
        {
            if ((*string_size) == 0)
                return;

            (*face_components) = append_to_int_array((*face_components), (*array_size), atoi((*string_buffer)));
            (*array_size)++;

            /*
             * in case that not exist vt and vn values in file.
             * keep the slash number for this case
             * */
            if (slash_number == 0)
            {
                (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
                (*array_size)++;
                (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
                (*array_size)++;
            }
            /*
                 * in case that not exist vn values in file.
                 * */
            else if ((*array_size) % 3 != 0)
            {
                (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
                (*array_size)++;
            }

            reset_string_buffer(string_size, string_buffer);
            return;
        }
        else
        {
            append_to_char_array((*string_buffer), (*string_size), read_character);
            (*string_size)++;
        }
    }
    else
    {
        /*
         * in case that not exist vt and vn values in file.
         * Differently, these components inside the line in this case
         * */
        if ((*string_size) == 1 && slash_number == 0)
        {
            (*face_components) = append_to_int_array((*face_components), (*array_size), atoi((*string_buffer)));
            (*array_size)++;

            (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
            (*array_size)++;
            (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
            (*array_size)++;

            reset_string_buffer(string_size, string_buffer);
        }
        else if ((*string_size) > 0)
        {
            (*face_components) = append_to_int_array((*face_components), (*array_size), atoi((*string_buffer)));
            (*array_size)++;

            /*
             * in case that not exist vn values in file.
             * */
            if ((*array_size) % 3 != 0)
            {
                (*face_components) = append_to_int_array((*face_components), (*array_size), 0);
                (*array_size)++;
            }
            reset_string_buffer(string_size, string_buffer);
        }
    }

    /* for recursive */
    parse_f_line(file, array_size, string_size, slash_number, string_buffer, face_components);
}

/*
 * starts to face line reading
 * */
int *read_face_line(FILE *file, int *array_size)
{
    int string_size = 0, slash_number = 0;
    char *string_buffer = calloc(1, sizeof(char));
    int *face_components = calloc(1, sizeof(int));

    parse_f_line(file, array_size, &string_size, slash_number, &string_buffer, &face_components);

    free(string_buffer);
    return face_components;
}

void reset_string_buffer(int *string_size, char **string_buffer)
{
    (*string_size) = 0;
    free((*string_buffer));
    (*string_buffer) = calloc(1, sizeof(char));
}

void append_to_char_array(char *array, const int array_size, const int character)
{
    array = realloc(array, (array_size + 1) * sizeof(char));
    array[array_size] = (char)character;
}

/*
 * Increment by 1024 allocates memory of the int array.
 * */
int *append_to_int_array(int *array, const int size, const int character)
{
    if (size % 1024 == 0)
        array = realloc(array, (size + 1024) * sizeof(int));
    array[size] = character;
    return array;
}

/*
 * vn are always followed by three floating point values
 * these are optional, there can be no vn lines in the file
 * */
double *read_vertex_normal_line(FILE *file)
{
    double *values = (double *)calloc(3, sizeof(double));

    fscanf(file, " %lf %lf %lf", &values[0], &values[1], &values[2]);

    return values;
}

/*
 * vt are always followed by two floating point values
 * these are optional, there can be no vt lines in the file
 * */
double *read_vertice_texture_line(FILE *file)
{
    double *values = (double *)calloc(2, sizeof(double));

    fscanf(file, " %lf %lf", &values[0], &values[1]);

    bool is_u_value_correct = 0.0 <= values[0] && values[0] <= 1.0;
    bool is_v_value_correct = 0.0 <= values[1] && values[1] <= 1.0;
    if (!is_u_value_correct && !is_v_value_correct)
        fprintf(stderr, "u or v value is wrong.\n");

    return values;
}

/*
 * v are always followed with three floating point values
 * these are non-optional, there must be some v lines in the file
 */
double *read_vertice_line(FILE *file)
{
    double *values = (double *)calloc(3, sizeof(double));

    fscanf(file, " %lf %lf %lf", &values[0], &values[1], &values[2]);

    return values;
}

void read_name(FILE *file, int *len, char **name)
{
    char read_character = (char)getc(file);
    if (read_character == '\n')
    {
        (*name)[(*len) - 1] = '\0';
        return;
    }
    (*name)[(*len) - 1] = read_character;
    (*name) = (char *)realloc((*name), ++(*len) * sizeof(char));
    read_name(file, len, name);
}

char *read_group_or_object_name_line(FILE *file)
{
    int len = 0;
    char *name = calloc(++len, sizeof(char));

    read_name(file, &len, &name);

    return name;
}

void read_comment_line(FILE *file)
{
    char read_character;

    read_character = (char)getc(file);
    if (read_character != '\n' && read_character != EOF)
        read_comment_line(file);
}
