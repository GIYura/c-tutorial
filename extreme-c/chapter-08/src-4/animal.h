#ifndef ANIMAL_H
#define ANIMAL_H

/*
NOTE: это базовый класс, от которого наследуются все остальные.
В данном примерем - класс cat и dog.
*/

/* forward declaration */
struct animal_t;

/*
@brief: Create animal (allocate memory)
@in: none
@out: struct animal_t*
*/
struct animal_t* AnimalCreate(void);

/*
@brief: Init animal
@in: struct animal_t*
@in: char* name - animal name
*/
void AnimalInit(struct animal_t* animal, const char* const name);

/*
@brief: Deinit animal
@in: struct animal_t*
@out: none
*/
void AnimalDeinit(struct animal_t* animal);

/*
@brief: Animal noise
@in: struct animal_t*
@out: none
*/
void AnimalSound(struct animal_t* animal);

#endif /* ANIMAL_H */

