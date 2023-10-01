#include <stdio.h>
#include <stdlib.h>

#include "person.h"
#include "student.h"

int main(int argc, char* argv[])
{
    struct student_t* m_student = StudentCreate();

    StudentInit(m_student, "John", "Doe", 1987, "TA5667", 134);

/* используем поведенческие функции объекта Person
для чтения атрибутов объекта Student */
    char buffer[32];

/* восходящее приведение указателя к родительскому типу */
    struct person_t* m_person = (struct person_t*)m_student;

    PersonGetFirstName(m_person, buffer);
    printf("First name: %s\n", buffer);
    PersonGetLastName(m_person, buffer);
    printf("Last name: %s\n", buffer);
    printf("Birth year: %d\n", PersonGetBirthYear(m_person));

/* теперь мы читаем атрибуты, принадлежащие объекту Student */
    StudentGetNumber(m_student, buffer);
    printf("Student number: %s\n", buffer);
    printf("Passed credits: %d\n", StudentGetPassedCredits(m_student));

/* уничтожаем и освобождаем объект Student */
    StudentDeinit(m_student);
    free(m_student);

    return 0;
}

