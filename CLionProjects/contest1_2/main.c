#include <stdio.h>
#include <stdlib.h>
void Primers(int n, int* p){
    int j = 0;
    for (int i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                p[j++] = i;
 //               printf("%d\n", p[j -1]);
                n /= i;
            }
        }

        if (n != 1) {
            p[j] = n;
 //           printf("%d\n", p[j]);
        }
}

int main() {
    int n;
    scanf("%d", &n);
    int *p;
    p = (int *) calloc(n, sizeof(int));
    Primers(n, p);
    for(int i = 0; i < n; ++i){
        if(p[i] == 0)
            break;
        printf("%d", p[i]);
    }
    return 0;
}
#include <Python.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    double *data;
    size_t N;
}array_t;


static void
Primers(size_t n, array_t first)
{
    size_t N = A->N;
    out->N = N;
    out->data = calloc(N * N, sizeof(*out->data));
    double res = 0.0;
    double a = 0.0;
    double b = 0.0;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            res = 0.0;
            for (size_t k = 0; k < N; ++k) {
                a = A->data[i * N + k];
                b = B_transposed->data[j * N + k];
                res += a*b;
            }
            out->data[i * N + j] = res;
        }
    }

}

//===============Python=============

typedef enum {
    NoError = 0,
    ArgumentTypeMismatch,
    RowTypeMismatch,
    ElementTypeMismatch,
}conversion_error_t;

static conversion_error_t
pyobject_to_matrix(PyObject *lists, size_t shape, matrix_t *out, bool transposed)
{
    out->N = shape;
    out->data = calloc(shape *shape, sizeof(*out->data));
    conversion_error_t err = NoError;

    if(!PyList_Check(lists)) {
        err = ArgumentTypeMismatch;
        goto fail;
    }
    size_t height = PyList_Size(lists);
    size_t row_width = 0;
    size_t plain_index = 0;
    double elem_value = 0.0;
    for(size_t i = 0; i < height; ++i){
        PyObject *row = PyList_GetItem(lists, i);
        if(!PyList_Check(row)) {
            err = RowTypeMismatch;
            goto fail;
        }
        row_width = PyList_Size(row);
        for (size_t j = 0; j < row_width; ++j) {
            PyObject* elem = PyList_GetItem(row, j);
            if(!PyNumber_Check(elem)) {
                err = ElementTypeMismatch;
                goto fail;
            }
            elem_value = PyFloat_AsDouble(elem);
            plain_index = transposed ? j*shape + i : i*shape + j;
            out->data[plain_index] = elem_value;
        }
    }
    return NoError;
    fail:
    if (out->data)
        free(out->data);
    out->data = NULL;
    out->N = 0;
    return err;
}

static PyObject*
matrix_to_pyobject(const matrix_t *mat)
{
    size_t N = mat->N;
    PyObject *result = PyList_New(N);
    for (size_t i = 0; i < N; ++i) {
        PyObject *row = PyList_New(N);
        PyList_SetItem(result, i, row);
        for (size_t j= 0; j < N; ++j) {
            PyObject *elem = PyFloat_FromDouble(mat->data[i*N + j]);
            PyList_SetItem(row, j, elem);
        }
        return result;
    }
}



static PyObject*
dot(PyObject* module, PyObject *args){
    matrix_t A, B, Res;
    PyObject *result = NULL;
    memset(&A, 0, sizeof(A));
    memset(&B, 0, sizeof(B));
    memset(&Res, 0, sizeof(Res));

    if (PyTuple_Size(args) < 3){
        goto end;
    }

    PyObject *py_shape = PyTuple_GetItem(args, 0);
    PyObject *py_A = PyTuple_GetItem(args, 1);
    PyObject *py_B = PyTuple_GetItem(args, 2);
    if (!PyLong_Check(py_shape)) {
        goto end;
    }
    size_t shape = PyLong_AsSize_t(py_shape);
    if(0 != pyobject_to_matrix(py_A, shape, &A, false) || 0!= pyobject_to_matrix(py_B, shape, &B, true))
    {
        goto end;
    }
    Py_BEGIN_ALLOW_THREADS
    matrix_dot(&A, &B, &Res);
    Py_END_ALLOW_THREADS

    result = matrix_to_pyobject(&Res);

    end:
    if(A.data) free(A.data);
    if(B.data) free(B.data);
    if(Res.data) free(Res.data);
    return result;
}


 PyMODINIT_FUNC PyInit_matrix(){
    static PyMethodDef methods[] = {
            {"dot", dot, METH_VARARGS, "Matrix dot"},
            {NULL, NULL, 0, NULL}
    };
    static PyModuleDef moduleDef = {
            PyModuleDef_HEAD_INIT,
            "Fast matrix functions",
            "matrix",
            -1,
            methods
    };
    return PyModule_Create(&moduleDef);
}
