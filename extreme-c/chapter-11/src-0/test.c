/* Это нужно, чтобы использовать элементы не из состава POSIX */
#define _GNU_SOURCE
#include <unistd.h>
/* Это не является частью POSIX! */
#include <sys/syscall.h>

int main(int argc, char* argv[]) 
{
    char message[20] = "Hello World!\n";
    /* Инициирует системный вызов 'write', который записывает
    некоторые байты в стандартный вывод. */
    
    /* 
    1 - номер системного вызова
    2 - дескриптор файла (1 - стандартный вывод)
    3 - указатель на буфер
    4 - кол-во байтов
    */
    syscall(__NR_write, 1, message, 13);

    return 0;
}

