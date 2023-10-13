#include <stdio.h>
#include <stdlib.h>

#include "student.h"

int main(int argc, char* argv[])
{
    struct student_t* m_student = StudentCreate();

    StudentInit(m_student, "John", "Doe", 1987, "TA5667", 134);

/* Мы должны использовать поведенческие функции объекта student,
так как его указатель нельзя привести к типу person и мы
не имеем доступа к приватному родительскому указателю
в объекте student.*/

    char buffer[32];

    StudentGetFirstName(m_student, buffer);
    printf("First name: %s\n", buffer);

    StudentGetLastName(m_student, buffer);
    printf("Last name: %s\n", buffer);

    printf("Birth year: %d\n", StudentGetBirthYear(m_student));
    StudentGetNumber(m_student, buffer);

    printf("Student number: %s\n", buffer);
    printf("Passed credits: %d\n", StudentGetPassedCredits(m_student));

/* уничтожаем и освобождаем объект Student */
    StudentDeinit(m_student);
    free(m_student);

    return 0;
}

