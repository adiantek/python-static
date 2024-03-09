#include <Python.h>
#include "python3api.h"

PyStatus python3api_init(int argc, char **argv) {
  PyStatus status;

  PyConfig config;
  PyConfig_InitPythonConfig(&config);
  status = PyConfig_SetBytesArgv(&config, argc, argv);
  if (PyStatus_Exception(status)) {
    PyConfig_Clear(&config);
    return status;
  }
  config.isolated = 1;
  PyWideStringList_Append(&config.module_search_paths, L"python.zip");
  config.module_search_paths_set = 1;
  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status)) {
    PyConfig_Clear(&config);
    return status;
  }
  PyConfig_Clear(&config);
  PyErr_Print();
  return status;
}

int python3api_finalize() {
  int status = Py_FinalizeEx();
  pymain_free();
  return status;
}

bool python3api_clear(const char *module_name) {
  PyObject* main_module = PyImport_AddModule(module_name);
  if (!main_module) {
    printf("PyImport_AddModule failed\n");
    PyErr_Print();
    return false;
  }
  PyObject* global_dict = PyModule_GetDict(main_module);
  if (!global_dict) {
    printf("PyModule_GetDict failed\n");
    PyErr_Print();
    return false;
  }
  PyDict_Clear(global_dict);
  return true;
}

char *python3api_eval(const char *module_name, const char *code, int start) {
  PyObject* main_module = PyImport_AddModule(module_name);
  if (!main_module) {
    printf("PyImport_AddModule failed\n");
    PyErr_Print();
    return 0;
  }
  PyObject* global_dict = PyModule_GetDict(main_module);
  if (!global_dict) {
    printf("PyModule_GetDict failed\n");
    PyErr_Print();
    return 0;
  }
  PyObject* code_obj = Py_CompileString(code, module_name, start);
  if (!code_obj) {
    printf("Py_CompileString failed\n");
    PyErr_Print();
    return 0;
  }
  PyObject* result = PyEval_EvalCode(code_obj, global_dict, global_dict);
  if (!result) {
    printf("PyEval_EvalCode failed\n");
    PyErr_Print();
    Py_DECREF(code_obj);
    return 0;
  }
  Py_DECREF(code_obj);

  if (PyUnicode_Check(result)) {
    const char *cstr = PyUnicode_AsUTF8(result);
    char *ret = strdup(cstr);
    Py_DECREF(result);
    return ret;
  } else if (result == Py_None) {
    return strdup("None");
  } else {
    printf("PyEval_EvalCode returned not a string\n");
    PyObject_Print(result, stdout, 0);
    return strdup("Invalid");
  }
}

void python3api_free(char *ptr) {
  if (ptr) {
    free(ptr);
  }
}
