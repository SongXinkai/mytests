/**g++ -o callpy callpy.cpp -I/usr/include/python2.7 -L/usr/lib64/python2.7/config -lpython2.7**/
#include <Python.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

using namespace std;
mutex mtx;

void py_save_load(int thread_id){
    mtx.lock();
    Py_Initialize() ;
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    mtx.unlock();
    mtx.lock();
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs;
    pName = PyString_FromString("np_file");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, "save_np");
    pArgs = PyTuple_New(2);
    int len = 10000;
    PyObject* tuple_0 = PyTuple_New(len);
    for (int i = 0; i < len; ++i){
      PyTuple_SetItem(tuple_0, i, Py_BuildValue("f",0.1*i));
    }
    stringstream ss;
    ss << "out" << thread_id << ".bin";
    string s = ss.str();
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("O", tuple_0));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s",s.c_str()));
    PyObject_CallObject(pFunc, pArgs);
    pFunc = PyDict_GetItemString(pDict, "load_np");
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s",s.c_str()));
    PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pName);
    Py_DECREF(tuple_0);
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
    mtx.unlock();
}

int main(int argc, char** argv){
    cout << std::dec << 15 << endl;
    vector<thread> ths;
    for (int i = 0; i < 8; ++i){
      ths.emplace_back(py_save_load, i);
    }
    for (auto& th: ths){
      th.join();
    }
    cout << "=============" << endl;
    return 0;
}
