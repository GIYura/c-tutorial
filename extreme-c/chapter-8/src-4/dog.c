#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"
#include "animal-p.h"

typedef struct
{
    animal_t animal;
} dog_t;

static void DogSound(void* context)
{
    animal_t* dog = (animal_t*)context;
    printf("%s: Woof\n", dog->name);
}

dog_t* DogCreate(void)
{
    return (dog_t*)malloc(sizeof(dog_t));
}

void DogInit(dog_t* dog, const char* const name)
{
    /* вызов функции родительского класса + восходящее приведение к родительскому классу */
    AnimalInit((struct animal_t*)dog, name);
    
    /* переопределение функции базового класса */
    dog->animal.sound = &DogSound;
}

void DogDeinit(dog_t* dog)
{
    AnimalDeinit((struct animal_t*)dog);
}

