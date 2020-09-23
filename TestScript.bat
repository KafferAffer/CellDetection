ECHO OFF
gcc runner.c cbmp.c main.c -o main.exe -std=c99
::Runs all with default values for TH and FS
ECHO Hit Enter to do all easy tests
PAUSE

::Easy
main.exe samples/easy/1EASY.bmp TestResults/easy/1EASY_inv.bmp
ECHO For EASY1
main.exe samples/easy/2EASY.bmp TestResults/easy/2EASY_inv.bmp
ECHO For EASY2
main.exe samples/easy/3EASY.bmp TestResults/easy/3EASY_inv.bmp
ECHO For EASY3
main.exe samples/easy/4EASY.bmp TestResults/easy/4EASY_inv.bmp
ECHO For EASY4
main.exe samples/easy/5EASY.bmp TestResults/easy/5EASY_inv.bmp
ECHO For EASY5
main.exe samples/easy/6EASY.bmp TestResults/easy/6EASY_inv.bmp
ECHO For EASY6
main.exe samples/easy/7EASY.bmp TestResults/easy/7EASY_inv.bmp
ECHO For EASY7
main.exe samples/easy/8EASY.bmp TestResults/easy/8EASY_inv.bmp
ECHO For EASY8
main.exe samples/easy/9EASY.bmp TestResults/easy/9EASY_inv.bmp
ECHO For EASY9
main.exe samples/easy/10EASY.bmp TestResults/easy/10EASY_inv.bmp
ECHO For EASY10
ECHO Hit Enter to do all medium tests
PAUSE

::Medium
main.exe samples/medium/1MEDIUM.bmp TestResults/medium/1MEDIUM_inv.bmp
ECHO For MEDIUM1
main.exe samples/medium/2MEDIUM.bmp TestResults/medium/2MEDIUM_inv.bmp
ECHO For MEDIUM2
main.exe samples/medium/3MEDIUM.bmp TestResults/medium/3MEDIUM_inv.bmp
ECHO For MEDIUM3
main.exe samples/medium/4MEDIUM.bmp TestResults/medium/4MEDIUM_inv.bmp
ECHO For MEDIUM4
main.exe samples/medium/5MEDIUM.bmp TestResults/medium/5MEDIUM_inv.bmp
ECHO For MEDIUM5
main.exe samples/medium/6MEDIUM.bmp TestResults/medium/6MEDIUM_inv.bmp
ECHO For MEDIUM6
main.exe samples/medium/7MEDIUM.bmp TestResults/medium/7MEDIUM_inv.bmp
ECHO For MEDIUM7
main.exe samples/medium/8MEDIUM.bmp TestResults/medium/8MEDIUM_inv.bmp
ECHO For MEDIUM8
main.exe samples/medium/9MEDIUM.bmp TestResults/medium/9MEDIUM_inv.bmp
ECHO For MEDIUM9
main.exe samples/medium/10MEDIUM.bmp TestResults/medium/10MEDIUM_inv.bmp
ECHO For MEDIUM10

ECHO HIT Enter to do all hard tests
PAUSE

::Hard
ECHO For HARD1
main.exe samples/hard/1HARD.bmp TestResults/hard/1HARD_inv.bmp
ECHO For HARD2
main.exe samples/hard/2HARD.bmp TestResults/hard/2HARD_inv.bmp
ECHO For HARD3
main.exe samples/hard/3HARD.bmp TestResults/hard/3HARD_inv.bmp
ECHO For HARD4
main.exe samples/hard/4HARD.bmp TestResults/hard/4HARD_inv.bmp
ECHO For HARD5
main.exe samples/hard/5HARD.bmp TestResults/hard/5HARD_inv.bmp
ECHO For HARD6
main.exe samples/hard/6HARD.bmp TestResults/hard/6HARD_inv.bmp
ECHO For HARD7
main.exe samples/hard/7HARD.bmp TestResults/hard/7HARD_inv.bmp
ECHO For HARD8
main.exe samples/hard/8HARD.bmp TestResults/hard/8HARD_inv.bmp
ECHO For HARD9
main.exe samples/hard/9HARD.bmp TestResults/hard/9HARD_inv.bmp
ECHO For HARD10
main.exe samples/hard/10HARD.bmp TestResults/hard/10HARD_inv.bmp

ECHO HIT Enter to do all impossible tests
PAUSE

::Impossible
ECHO For IMPOSSIBLE1
main.exe samples/impossible/1IMPOSSIBLE.bmp TestResults/impossible/1IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE2
main.exe samples/impossible/2IMPOSSIBLE.bmp TestResults/impossible/2IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE3
main.exe samples/impossible/3IMPOSSIBLE.bmp TestResults/impossible/3IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE4
main.exe samples/impossible/4IMPOSSIBLE.bmp TestResults/impossible/4IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE5
main.exe samples/impossible/5IMPOSSIBLE.bmp TestResults/impossible/5IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE6
main.exe samples/impossible/6IMPOSSIBLE.bmp TestResults/impossible/6IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE7
main.exe samples/impossible/7IMPOSSIBLE.bmp TestResults/impossible/7IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE8
main.exe samples/impossible/8IMPOSSIBLE.bmp TestResults/impossible/8IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE9
main.exe samples/impossible/9IMPOSSIBLE.bmp TestResults/impossible/9IMPOSSIBLE_inv.bmp
ECHO For IMPOSSIBLE10
main.exe samples/impossible/10IMPOSSIBLE.bmp TestResults/impossible/10IMPOSSIBLE_inv.bmp

PAUSE