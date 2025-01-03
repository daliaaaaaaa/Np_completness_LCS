@echo off

echo Compiling...
gcc Menu.c DFS\DFS_LCS.c A_etoile\LCS_A_etoile.c LCS\lcs.c BFS_LCS\bfs.c -o main

if %errorlevel% equ 0 (
    .\main
) else (
    echo Compilation failed.
)
pause