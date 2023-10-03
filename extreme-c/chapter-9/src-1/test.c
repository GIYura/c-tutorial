#include <stddef.h> /* определен макрос offsetof() */
#include <string.h>
#include <stdio.h>

/* если не сделать приведение к char*, то макрос вернет количество элементов
пример: 
x имеет адрес 0х100
&x + 1 - 0x104
&x + 1 - &x = (0x104 - 0x100) / sizeof x = 4 / 4 = 1 элемент м/у адресами
*/
#define SIZEOF(x) ((char*)(&x + 1) - (char*)&x)

typedef struct
{
    unsigned char a0;
    unsigned char a1;
} a_t;

typedef struct 
{
    unsigned char b0;
    unsigned char b1;
} b_t;

/* структура наследник типа a_t и b_t */
typedef struct 
{
    a_t a;
    b_t b;
    unsigned char c0;
    unsigned char c1;
} c_t;

/* структура для демонстрации offsetof() */
typedef struct
{
    unsigned char c;
    unsigned int i;
    unsigned short s;
    double d;
} d_t;
    
int main(int argc, char* argv[]) 
{
    c_t c_obj;  /* объект типа c_t */

    /* заполнение полей структуры */
    c_obj.a.a0 = 0xa0;    
    c_obj.a.a1 = 0xa1;

    c_obj.b.b0 = 0xb0;
    c_obj.b.b1 = 0xb1;

    c_obj.c0 = 0xc0;
    c_obj.c1 = 0xc1;

    /* демострация правильного и неправильного приведения типов */
    a_t* aPtr = (a_t*)(&c_obj); /* правильно */
#if 1 
    b_t* bPtr = (b_t*)(&c_obj); /* неправильно: bPtr указывает на поле a0 */
#else
    b_t* bPtr = (b_t*)((char*)&c_obj + sizeof(a_t)); /* правильно: bPtr указывает на поле b0 */
#endif
    c_t* cPtr = &c_obj; /* правильно */

    /* при неправильном приведении типов, все указатели имееют один и тот же адрес,
    при правильном приведении, bPtr указавает на поле b в стркутуре c_obj */
    printf("aPtr: %p\n", (void*)aPtr);
    printf("bPtr: %p\n", (void*)bPtr);
    printf("cPtr: %p\n", (void*)cPtr);

    /* значения по адресам */
    printf("a0 = 0x%x\n", aPtr->a0);
    printf("b0 = 0x%x\n", bPtr->b0);
    printf("c0 = 0x%x\n", cPtr->c0);

    /* демо работы макроса offsetof() */
    printf("offsets: c = %ld\n", (long) offsetof(d_t, c));
    printf("offsets: i = %ld\n", (long) offsetof(d_t, i));
    printf("offsets: s = %ld\n", (long) offsetof(d_t, s));
    printf("offsets: d = %ld\n", (long) offsetof(d_t, d));

    /* демо работы как макрос offsetof() устроен изнутри
    -- offsetof() macro returns the number of bytes of offset before a 
    particular element of a struct or union.
    -- offsetof() macro takes two parameters. 
    The first parameter is the structure name; the second, the name of the structure element.
    
    1. ((s *)0): takes the integer zero and casts it as a pointer to s.
    2. ((s *)0)->m: dereferences that pointer to point to structure member m.
    3. &(((s *)0)->m): computes the address of m.
    4. (size_t)&(((s *)0)->m): casts the result to an appropriate data type. 
    */
    printf("offsets: c = %ld\n", (size_t)&(((d_t *)0)->c));
    printf("offsets: i = %ld\n", (size_t)&(((d_t *)0)->i));
    printf("offsets: s = %ld\n", (size_t)&(((d_t *)0)->s));
    printf("offsets: d = %ld\n", (size_t)&(((d_t *)0)->d));

    /* ЗАМЕЧАНИЕ: ограничение использования макроса SIZEOF:
    нельзя использовать тип в качастве аргумента, только переменную */
    printf("sizeof int: %ld\n", sizeof(int));
    int x = 10;
    printf("SIZEOF int: %ld\n", SIZEOF(x));

    return 0;
}

