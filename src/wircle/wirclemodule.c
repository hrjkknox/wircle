#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <stdlib.h>

typedef struct {
	double x;
	double y;
} Point;

Point getPoint(double rad, double amp, double angle, int num, Point centre) {
	Point result;
	result.x = (rad + amp * sin(num * angle)) * cos(angle) + centre.x;
	result.y = (rad + amp * sin(num * angle)) * sin(angle) + centre.y;
	return result;
}

int getScaledTau(int scale) {
	return (int) ((M_PI * 2) * pow(10, (double) scale));
}

Point *getPoints(double rad, double amp, int num, Point centre, int res) {
	int limit = getScaledTau(res);
	Point *result = calloc(limit, sizeof(Point));
	
	for (int i = 0; i < limit; i++) {
		result[i] = getPoint(rad, amp, i / pow(10, (double) res), num, centre);
	}
	return result;
}

PyObject *pointToTuple(Point p) {
	PyObject *tuple = PyTuple_New(2);
	PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(p.x));
	PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(p.y));
	return tuple;
}

PyObject *pointsToList(Point *points, int len) {
	PyObject *list = PyList_New(len);
	for (int i = 0; i < len; i++) {
		PyObject *tuple = pointToTuple(points[i]);
		PyList_SetItem(list, i, tuple);
	}
	return list;
}

static PyObject *wircle_getPoint(PyObject *self, PyObject *args) {
	/* Arguments received from the python function */
	double rad;
	double amp;
	double angle;
	int num;
	Point centre;

	if (!PyArg_ParseTuple(args, "dddi(dd)", &rad, &amp, &angle, &num, &centre.x, &centre.y)) {
		return NULL;
	}

	Point result = getPoint(rad, amp, angle, num, centre);
	PyObject *x = PyFloat_FromDouble(result.x);
	PyObject *y = PyFloat_FromDouble(result.y);
	PyObject *output = PyTuple_Pack(2, x, y);
	Py_DECREF(x);
	Py_DECREF(y);
	return output;
}

static PyObject *wircle_getPoints(PyObject *self, PyObject *args) {
	/* Arguments received from the python function*/
	double rad;
	double amp;
	int num;
	Point centre;
	int res;
	
	if (!PyArg_ParseTuple(args, "ddi(dd)i", &rad, &amp, &num, &centre.x, &centre.y, &res)) {
		return NULL;
	}
	

	Point *result = getPoints(rad, amp, num, centre, res);
	int resultSize = getScaledTau(res);
	PyObject *output = pointsToList(result, resultSize);
	if (!output) {
		return NULL;
	}

	free(result);
	return output;
}

static PyMethodDef methodsArray[] = {
	{"getPoint", wircle_getPoint, METH_VARARGS, NULL},
	{"getPoints", wircle_getPoints, METH_VARARGS, NULL},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef wircle = {
	PyModuleDef_HEAD_INIT,
	"wircle",
	NULL,
	-1,
	methodsArray
};

PyMODINIT_FUNC PyInit_wircle(void) {
	return PyModule_Create(&wircle);
}
