ECHO OFF
gcc runner.c cbmp.c main.c -o main.exe -std=c99

main.exe samples/easy/1EASY.bmp TestResults/easy/1EASY_inv.bmp
ECHO For EASY1
PAUSE