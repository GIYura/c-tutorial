#### Ручная сборка проекта

```
/* создание директории для сборки */
mkdir -p build

/* компиляция .c файлов в объектные  */
gcc -c math/add.c -o build/add.o
gcc -c math/sub.c -o build/sub.o
gcc -c math/mul.c -o build/mul.o
gcc -c math/div.c -o build/div.o

/* создание статичаской библиотеки из объектных файлов */
ar rcs build/libcalc.a build/add.o build/mul.o build/sub.o build/div.o 

/* компиляция основного файла + интерфейсный файл статической библиотеки */
gcc -c -Imath exec/test.c -o build/test.o

/* линковка основного файла с статической библиотекой */
gcc -Lbuild build/test.o -lcalc -o build/test.out
```
