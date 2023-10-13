#ifndef DOG_H
#define DOG_H

/*
NOTE: дочерний класс.
*/

/* forward declaration */
struct dog_t;

/*
@brief: Create вщп (allocate memory)
@in: none
@out: struct pesron_t*
*/
struct dog_t* DogCreate(void);

/*
@brief: Init dog
@in: struct dog_t*
@in: char* name - dog name
@out: none
*/
void DogInit(struct dog_t* dog, const char* const name);

/*
@brief: Deinit dog
@in: struct dog_t*
@out: none
*/
void DogDeinit(struct dog_t* dog);

#endif /* DOG_H */

