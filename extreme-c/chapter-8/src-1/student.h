#ifndef STUDENT_H
#define STUDENT_H

/* forward declaration */
struct student_t;

/*
@brief: Create student (allocate memory)
@in: none
@out: struct student_t*
*/
struct student_t* StudentCreate(void);

/*
@brief: Init student
@in: struct student_t*
@out: none
*/
void StudentInit(struct student_t* student, 
                const char* const firstName,
                const char* const lastName,
                unsigned int year,
                const char* const stdNumber,
                unsigned int passedCredits);

/*
@brief: Deinit student
@in: struct student_t*
@out: none
*/
void StudentDeinit(struct student_t* student);

/*
@brief: Get student number
@in: struct student_t*
@in: char* buffer to store number
@out: none
*/
void StudentGetNumber(struct student_t* student, char* stdNumber);

/*
@brief: Get student passed credits
@in: struct student_t*
@out: none
*/
unsigned int StudentGetPassedCredits(struct student_t* student);

#endif /* STUDENT_H */

