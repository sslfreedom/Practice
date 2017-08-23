#include "Python.h"

static PyObject *treble(PyObject *self, PyObject *args) {
    int num;
    PyObject *retval; 
    int res = PyArg_ParseTuple(args, "i", &num);
    if (!res) {
        return NULL;
    }
    res = num * 3;
    retval = (PyObject*)Py_BuildValue("i", res);
    return retval;
}

static PyMethodDef
ExtestMethods[] = {
    {"treble", treble, METH_VARARGS},
    {NULL, NULL},
};

void initExtest() {
    Py_InitModule("Extest", ExtestMethods);
}
