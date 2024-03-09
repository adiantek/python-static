#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef Py_PYTHON_H
// src:
// https://github.com/python/cpython/blob/6abddd9f6afdddc09031989e0deb25e301ecf315/Include/cpython/initconfig.h#L10
typedef struct {
  enum {
    _PyStatus_TYPE_OK = 0,
    _PyStatus_TYPE_ERROR = 1,
    _PyStatus_TYPE_EXIT = 2
  } _type;
  const char *func;
  const char *err_msg;
  int exitcode;
} PyStatus;

// src:
// https://github.com/python/cpython/blob/6abddd9f6afdddc09031989e0deb25e301ecf315/Include/compile.h#L8
#define Py_single_input 256
#define Py_file_input 257
#define Py_eval_input 258
#endif

PyStatus python3api_init(int argc, char **argv);
int python3api_finalize();
bool python3api_clear(const char *module_name);
char *python3api_eval(const char *module_name, const char *code, int start);
void python3api_free(char *ptr);

#ifdef __cplusplus
}
#endif
