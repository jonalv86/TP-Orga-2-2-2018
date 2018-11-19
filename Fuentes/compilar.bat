del enmascarador.obj
del enmascarador.exe
nasm -f win32 enmascarador.asm
C:\MinGW\bin\gcc enmascarador.c enmascarador.obj -o enmascarador.exe
pause