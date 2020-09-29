ECHO OFF
gcc runner.c cbmp.c main.c -o main.exe -std=c99
PAUSE
echo >> table.txt
echo Easy1>> table.txt
for /l %%f in (1, 2, 35) do (
	for /l %%t in (60, 10, 230) do (
		main.exe samples/easy/1EASY.bmp TestResults/easy/1EASY_inv.bmp %%f %%t >> table.txt
	)
	echo >> table.txt
)

echo >> table.txt
echo Medium>> table.txt

for /l %%f in (1, 2, 35) do (
	for /l %%t in (60, 10, 230) do (
		main.exe samples/medium/1MEDIUM.bmp TestResults/meduim/1MEDIUM_inv.bmp %%f %%t >> table.txt
	)
	echo >> table.txt
)

echo >> table.txt
echo Hard>> table.txt

for /l %%f in (1, 2, 35) do (
	for /l %%t in (60, 10, 230) do (
		main.exe samples/hard/1HARD.bmp TestResults/hard/1HARD_inv.bmp %%f %%t >> table.txt
	)
	echo >> table.txt
)

echo >> table.txt
echo Impossible1>> table.txt

for /l %%f in (1, 2, 35) do (
	for /l %%t in (60, 10, 230) do (
		main.exe samples/impossible/1IMPOSSIBLE.bmp TestResults/impossible/1IMPOSSIBLE_inv.bmp %%f %%t >> table.txt
	)
	echo >> table.txt
)
PAUSE