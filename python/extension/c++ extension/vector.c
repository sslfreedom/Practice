#include <Python.h>

typedef struct {
    PyListObject list;
} vec;


static PyObject *get(vec *self, PyObject *args) {
    int arg;
    PyObject *retval;
    int res = PyArg_ParseTuple(args, "i", &arg);
    if (!res) return NULL;
    retval = self->list.ob_item[arg];
    return retval;
}

static PyObject *set(vec *self, PyObject *args) {
    int arg1;
    PyObject *arg2;
    PyObject *retval;
    int res = PyArg_ParseTuple(args, "iO", &arg1, &arg2);
    if (!res ) return NULL;
    retval = (self->list.ob_item[arg1] = arg2);
    return retval;
}

static int
Vec_init(vec *self, PyObject *args, PyObject *kwds)
{
    if (PyList_Type.tp_init((PyObject *)self, args, kwds) < 0)
        return -1;
    return 0;
}

static PyMethodDef Vec_methods[] = {
    {"get", (PyCFunction)get, METH_VARARGS},
    {"set", (PyCFunction)set, METH_VARARGS},
    {NULL, NULL},
};

static PyTypeObject VecType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        "vector.vec",         /* tp_name */
    sizeof(vec),          /* tp_basicsize */
    0,                       /* tp_itemsize */
    0,                       /* tp_dealloc */
    0,                       /* tp_print */
    0,                       /* tp_getattr */
    0,                       /* tp_setattr */
    0,                       /* tp_compare */
    0,                       /* tp_repr */
    0,                       /* tp_as_number */
    0,                       /* tp_as_sequence */
    0,                       /* tp_as_mapping */
    0,                       /* tp_hash */
    0,                       /* tp_call */
    0,                       /* tp_str */
    0,                       /* tp_getattro */
    0,                       /* tp_setattro */
    0,                       /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE, /* tp_flags */
    0,                       /* tp_doc */
    0,                       /* tp_traverse */
    0,                       /* tp_clear */
    0,                       /* tp_richcompare */
    0,                       /* tp_weaklistoffset */
    0,                       /* tp_iter */
    0,                       /* tp_iternext */
    Vec_methods,          /* tp_methods */
    0,                       /* tp_members */
    0,                       /* tp_getset */
    0,                       /* tp_base */
    0,                       /* tp_dict */
    0,                       /* tp_descr_get */
    0,                       /* tp_descr_set */
    0,                       /* tp_dictoffset */
    (initproc)Vec_init,   /* tp_init */
    0,                       /* tp_alloc */
    0,                       /* tp_new */
};

void
initvector() {
    PyObject *m;
    VecType.tp_base = &PyList_Type;
    if (PyType_Ready(&VecType) < 0)
        return;
    m = Py_InitModule3("vector", NULL, "vector module");
    if (m == NULL)
        return;
    Py_INCREF(&VecType);
    PyModule_AddObject(m, "vec", (PyObject *) &VecType);
}
