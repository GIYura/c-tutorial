#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

/* inheritance  */
typedef struct
{
    char* stdNumber;
    unsigned int passedCredits;
    struct person_t* person;
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
    student->person = PersonCreate();
    PersonInit(student->person, firstName, lastName, year);

    student->stdNumber = (char*)malloc(sizeof(char) * 16);
    strcpy(student->stdNumber, stdNumber);
    student->passedCredits = passedCredits;
}

void StudentDeinit(student_t* student)
{
    free(student->stdNumber);
    PersonDeinit(student->person);
    free(student->person);/* parent should be destroyed last */
}

void StudentGetFirstName(student_t* student, char* name)
{
    PersonGetFirstName(student->person, name);
}

void StudentGetLastName(student_t* student, char* name)
{
    PersonGetLastName(student->person, name);
}

unsigned int StudentGetBirthYear(student_t* student)
{
    return PersonGetBirthYear(student->person);
}

void StudentGetNumber(student_t* student, char* stdNumber)
{
    strcpy(stdNumber, student->stdNumber);
}

unsigned int StudentGetPassedCredits(student_t* student)
{
    return student->passedCredits;
}

