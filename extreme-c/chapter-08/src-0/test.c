#include <stdio.h>

typedef struct 
{
    char firstName[32];
    char lastName[32];
    unsigned int birthYear;
} person_t;

typedef struct
{
    person_t person;
    char studentNumber[16];
    unsigned int passedCredits;
} student_t;

int main(int argc, char* argv[])
{
    student_t m_student;
    student_t* pStudent = &m_student;

    /*literaly means: every student is a person */
    person_t* pPerson = (person_t*)&m_student;

    printf("Student address: %p\n", (void*)pStudent);
    printf("Person address:  %p\n", (void*)pPerson);

    return 0;
}

