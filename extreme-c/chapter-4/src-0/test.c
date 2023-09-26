/*
1. Compile source:
gcc test.c -o test.o
2. Run command size:
size test.o
*/
/*
NOTE:
global uninitialized and zeroed variables reside in BSS
*/
int gValue1;
int gValue2;
int gValue3 = 0;

/*
NOTE: global initialized variables reside in DATA
*/
int gValue4 = 10;
int gValue5 = 100;

/*
NOTE:
'static' uninitialized variable reside in DATA.
'static' initialized variable resides in BSS.
*/

int main(int argc, char* argv[])
{
    return 0;
}

