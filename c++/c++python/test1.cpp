/**g++ -o callpy callpy.cpp -I/usr/include/python2.7 -L/usr/lib64/python2.7/config -lpython2.7**/
#include <Python.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <unistd.h>

using namespace std;

void py_save_load(){
  int j = 0;
  Py_Initialize() ;
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('./')");
  PyObject *pName,*pModule,*pDict,*pFunc;
  pName = PyString_FromString("show_ndarray");
  pModule = PyImport_Import(pName);
  pDict = PyModule_GetDict(pModule);
  pFunc = PyDict_GetItemString(pDict, "show_array");
  while(true){
    int len = 1024*1024;
    PyObject* pArgs = PyTuple_New(2);
    PyObject* tuple_0 = PyTuple_New(len);
    PyObject* list_0 = PyList_New(0);
    for (int i = 0; i < len; ++i){
      PyTuple_SetItem(tuple_0, i, Py_BuildValue("f",0.1*i));
      PyList_Append(list_0, Py_BuildValue("d",i));
    }
    PyTuple_SetItem(pArgs, 0, tuple_0);
    PyTuple_SetItem(pArgs, 1, list_0);
    PyObject_CallObject(pFunc, pArgs);

    Py_DECREF(tuple_0);
    Py_DECREF(list_0);
    Py_DECREF(pArgs);
    cout << j++ << endl;
    sleep(1);
  }
  Py_DECREF(pName);
  Py_DECREF(pModule);
}

int main(int argc, char** argv){
    py_save_load();
    cout << "=============" << endl;
    return 0;
}
