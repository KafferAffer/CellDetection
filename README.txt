To compile this code run the following command prompt:
gcc runner.c cbmp.c main.c -o main.exe -std=c99
Then to run it use the following code where [framesize] and [threshold] are optional
main.exe example.bmp RESULT.bmp [framesize] [threshold]

If instead one wishes to run the functional tests compile the program as follows:
gcc tester.c cbmp.c main.c -o test.exe -std=c99
and run it like this:
test.exe 
A series of tests will be either passed or failed and a function name as well as test nr will be shown to guide you to what test failed

The ***TOMMYS ANSVAR*** bat file lets the user get a long list of cellcounts from diffrent threshholds and framesizes.

