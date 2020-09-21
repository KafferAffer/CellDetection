ECHO OFF
gcc runner.c cbmp.c main.c -o main.exe -std=c99
PAUSE
for /l %%f in (1, 2, 51) do (
	for /l %%t in (60, 10, 230) do (
		main.exe samples/easy/1EASY.bmp TestResults/easy/1EASY_inv.bmp %%f %%t
		ECHO For %%f / %%t EASY1
	)
	PAUSE
	cls
)
PAUSE