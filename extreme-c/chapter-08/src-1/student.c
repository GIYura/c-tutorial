#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "person-p.h"

/* inheritance  */
typedef struct
{
/*
NOTE: благодаря этой вложенности мы наследуем все атрибуты класса Person
и получаем доступ ко всем его поведенческим функциям.
Данная переменная должна быть первым полем структуры, 
иначе мы теряем возможность использования поведенческих функций класса Person.
*/
    person_t person;
    char* stdNumber;
    unsigned int passedCredits;
} student_t;

student_t* StudentCreate(void)
{
    return (student_t*)malloc(sizeof(student_t));
}

void StudentInit(student_t* student, 
                const char* const firstName,
                const char* const lastName,
                unsigned int year,
                const char* const stdNumber,
                unsigned int passedCredits)
{
    /* вызов функции родительского класса + восходящее приведение к родительскому классу */
    PersonInit((struct person_t*)student, firstName, lastName, year);
    student->stdNumber = (char*)malloc(sizeof(char) * 16);
    strcpy(student->stdNumber, stdNumber);
    student->passedCredits = passedCredits;
}

void StudentDeinit(student_t* student)
{
    free(student->stdNumber); /* fist destroy derived object */
    PersonDeinit((struct person_t*)student); /* destroy parent object */
}

void StudentGetNumber(student_t* student, char* stdNumber)
{
    strcpy(stdNumber, student->stdNumber);
}

unsigned int StudentGetPassedCredits(student_t* student)
{
    return student->passedCredits;
}

