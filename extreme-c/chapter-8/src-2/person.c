#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char firstName[32];
    char lastName[32];
    unsigned int year;
} person_t;

person_t* PersonCreate(void)
{
    return (person_t*)malloc(sizeof(person_t));
}

void PersonInit(person_t* person,
                const char* const firstName,
                const char* const lastName,
                unsigned int year)
{
    strcpy(person->firstName, firstName);
    strcpy(person->lastName, lastName);
    person->year = year;
}

void PersonDeinit(person_t* person)
{
    /* nothing to do */
}

void PersonGetFirstName(person_t* person, char* firstName)
{
    strcpy(firstName, person->firstName);
}

void PersonGetLastName(person_t* person, char* lastName)
{
    strcpy(lastName, person->lastName);
}

unsigned int PersonGetBirthYear(person_t* person)
{
    return person->year;
}

