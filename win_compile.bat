cl /nologo /c /MT /O2 /D Py_NO_ENABLE_SHARED python3api.c -I cpython\Include -I cpython\PC -I .
lib /nologo /OUT:python3api.lib python3api.obj cpython\PCbuild\%1\python312.lib
cl /nologo /O2 /D Py_NO_ENABLE_SHARED /D PYTHON3API_TEST python3api.c -I cpython\Include -I cpython\PC -I . cpython\PCbuild\%1\python312.lib
