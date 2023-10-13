#ifndef PERSON_H
#define PERSON_H

/*
Это интерфейсная часть класса Person
*/

/* forward declaration */
struct person_t;

/*
@brief: Create person (allocate memory)
@in: none
@out: struct pesron_t*
*/
struct person_t* PersonCreate(void);

/*
@brief: Init person
@in: struct person_t*
@out: none
*/
void PersonInit(struct person_t* person,
                const char* const firstName,
                const char* const lastName,
                unsigned int year);

/*
@brief: Deinit person
@in: struct person_t*
@out: none
*/
void PersonDeinit(struct person_t* person);

/*
@brief: Get first name of a person
@in: struct person_t*
@in: char* buffer to store name
@out: none
*/
void PersonGetFirstName(struct person_t* person, char* firstName);

/*
@brief: Get last name of a person
@in: struct person_t*
@in: char* buffer to store name
@out: none
*/
void PersonGetLastName(struct person_t* person, char* lastName);

/*
@brief: Get date of birth of a person
@in: struct person_t*
@out: none
*/
unsigned int PersonGetBirthYear(struct person_t* person);

#endif /* PERSON_H */

