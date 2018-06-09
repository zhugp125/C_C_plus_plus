#include <iostream>
#include <Python.h>

using namespace std;

void usePythonByApi()
{
    //初始化python
    Py_Initialize();

    //检查初始化是否成功
    if (!Py_IsInitialized())
    {
        return -1;
    }

    //添加当前路径
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("print '----import sys----'");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs;

    // 载入脚本
    pName = PyString_FromString("pytest");
    pModule = PyImport_Import(pName);
    if (!pModule)
    {
        cout << "can't find pytest.py\n";
        return -1;
    }

    pDict = PyModule_GetDict(pModule);
    if (!pDict)
    {
        return -1;
    }

    // 找到函数名为add的函数
    pFunc = PyDict_GetItemString(pDict, "add");
    if (!pFunc || !PyCallable_Check(pFunc))
    {
        cout << "can't find function [add]\n";
        return -1;
    }

    // 构造参数
    pArgs = PyTuple_New(2);

    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 3));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));

    // 调用python函数
    PyObject* retValue = PyObject_CallObject(pFunc, pArgs);

    //  解析返回的结果
    int i = 0;
    PyArg_Parse(retValue, "i", &i);
    cout << "add return : " << i << "\n";

    // 解除对象引用
    Py_DECREF(pName);
    Py_DECREF(pArgs);
    Py_DECREF(pModule);

    Py_Finalize();
}

int main()
{


    cout << "Hello World!" << endl;
    return 0;
}
