@REM filepath: /C:/Users/TRETEC/Desktop/Np_completness_LCS/compile_and_run.bat
@echo off

echo Compiling...
gcc -o menu Menu.c DFS\DFS_LCS.c A_etoile\LCS_A_etoile.c

echo Running...
menu.exe

pause