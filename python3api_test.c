#ifdef _MSC_VER
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Bcrypt.lib")
#pragma comment(lib, "Pathcch.lib")
#endif

#include "python3api.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  printf("python3api_init: %s\n", python3api_init(argc, argv).err_msg);
  PyErr_Clear();
  {
    char *ret = python3api_eval("__api__", "def foo():\n  print('Hello from Python!')\n  return 123\ndef bar():\n  return foo()", Py_file_input);
    printf("ret: %s\n", ret);
    free(ret);
  }
  {
    char *ret = python3api_eval("__api__", "import json", Py_file_input);
    printf("ret: %s\n", ret);
    free(ret);
  }
  {
    char *ret = python3api_eval("__api__", "import sys", Py_file_input);
    printf("ret: %s\n", ret);
    free(ret);
  }
  {
    char *ret = python3api_eval("__api__", "json.dumps(bar())", Py_eval_input);
    printf("ret: %s\n", ret);
    free(ret);
  }
  python3api_clear("__api__");
  {
    char *ret = python3api_eval("__api__", "json.dumps(bar())", Py_eval_input);
    printf("ret: %s\n", ret);
    free(ret);
  }
  
  python3api_finalize();
  return 0;
}