#include <Python.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "ppm.h"

struct ppm *set_ppm(int *ppm_content, int size_of_ppm) {
    struct ppm *ppm = calloc(1, sizeof(struct ppm));

    ppm->type = ppm_content[0] == 1 ? "P3": "P6";
    ppm->width = ppm_content[1];
    ppm->height = ppm_content[2];
    ppm->max_value = ppm_content[3];

    if (ppm->width * ppm->height != (size_of_ppm - 4) / 3) {
        printf("ppm file size error.\n");
    }
    ppm->size = size_of_ppm;

    int number_per_channel = ppm->width * ppm->height;
    ppm->R = calloc(number_per_channel, sizeof(int));
    ppm->G = calloc(number_per_channel, sizeof(int));
    ppm->B = calloc(number_per_channel, sizeof(int));

    for (size_t i = 4, j = 0; i < ppm->size; i += 3, j++) {
        ppm->R[j] = ppm_content[i];
        ppm->G[j] = ppm_content[i + 1];
        ppm->B[j] = ppm_content[i + 2];
    }

    return ppm;
}

int read_ppm_array(PyObject *list, int **output_array, int *output_size) {
    Py_ssize_t i, n;
    PyObject *item;
    long value;

    n = PyList_Size(list);
    if (n < 0)
        return 1; /* Not a list */

    int *int_array = (int *) calloc(n, sizeof(int));
    if (int_array == NULL)
        return 1; /* Not a list */

    /* P3 or P6 */
    item = PyList_GetItem(list, 0);
    char *str = PyString_AsString(item);
    int_array[0] = strcmp(str, "P3") ? 0 : 1;

    for (i = 1; i < n; i++) {
        item = PyList_GetItem(list, i); /* Can't fail */
        if (!PyString_Check(item))
            continue; /* Skip non-string */

        value = atoi(PyString_AsString(item));
        if (value == -1 && PyErr_Occurred())
            /* Integer too big to fit in a C long, bail out */
            return 1;

        int_array[i] = value;
    }
    *output_array = int_array;
    (*output_size) = (int) n;
    return 0;
}

struct ppm *read_ppm_file(const char *python_file, const char *python_function, const char *ppm_file) {
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    int *ppm_contents = NULL, size_of_ppm = 0;
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;    
    } 

    /* initialize the python system */
    Py_Initialize();

    /* SET PYTHON FILE PATH */
    PySys_SetPath(cwd);

    /* convert the ASCII module name to a Python object (file) */
    pName = PyString_FromString(python_file);

    /* import the module named on the command line (the file name) */
    pModule = PyImport_Import(pName);

    /* decrease the number of references on the object */
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pythonArgument;
        pythonArgument = PyTuple_New(1);

        pValue = PyString_FromString(ppm_file);
        if (pValue == NULL) {
            return NULL;
        }
        PyTuple_SetItem(pythonArgument, 0, pValue);

        pFunc = PyObject_GetAttrString(pModule, python_function);
        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc, pythonArgument);
            if (pValue != NULL) {
                if (read_ppm_array(pValue, &ppm_contents, &size_of_ppm) != 0) {
                    PyErr_Print();
                    fprintf(stderr, "error : ppm array wasn't read : %s\n", python_file);
                    return NULL;
                }
            } else {
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", python_function);
        }
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", python_file);
        return NULL;
    }

    struct ppm* ppm = set_ppm(ppm_contents, size_of_ppm);
    return ppm;
}

void print_ppm_content(const struct ppm* ppm){
    printf("%s\n", ppm->type);
    printf("%d ", ppm->width);
    printf("%d\n", ppm->height);
    printf("%d\n", ppm->max_value);

    for (int i = 0; i < ppm->width; ++i) {
        for (int j = 0; j < ppm->height; ++j) {
            printf("%d ", ppm->R[i * ppm->width + j]);
            printf("%d ", ppm->G[i * ppm->width + j]);
            printf("%d  ", ppm->B[i * ppm->width + j]);
        }
        printf("\n");
    }

}
void print_ppm_content2(const struct ppm* ppm){
    printf("PPM\n");
    printf("%d,", ppm->width);
    printf("%d\n", ppm->height);

    for (int i = 0; i < ppm->width * ppm->height; ++i) {
        printf("%d,", ppm->R[i]);
        printf("%d,", ppm->G[i]);
        printf("%d,", ppm->B[i]);
        printf("255");
        printf("\r\n");
    }

}

void free_ppm(struct ppm* ppm){
    free(ppm->R);
    free(ppm->G);
    free(ppm->B);
    free(ppm);
}
