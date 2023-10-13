#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "animal-p.h"

static void Sound(void* context)
{
    animal_t* animal = (animal_t*)context;
    printf("%s: Beep\n", animal->name);
}

animal_t* AnimalCreate(void)
{
    return (animal_t*)malloc(sizeof(animal_t));
}

void AnimalInit(animal_t* animal, const char* const name)
{
    assert(animal);

    animal->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(animal->name, name);

    /* функция по умолчанию, если в дочернем классе она не будет переопределена,
    то будет вызвана функция по умолчанию. */
    animal->sound = &Sound;
}

void AnimalDeinit(animal_t* animal)
{
    free(animal->name);
}

void AnimalSound(animal_t* animal)
{
    (*animal->sound)(animal);
}

