#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"
#include "animal-p.h"

typedef struct
{
    animal_t animal;
} cat_t;

static void CatSound(void* context)
{
    animal_t* cat = (animal_t*)context;
    printf("%s: Meow\n", cat->name);
}

cat_t* CatCreate(void)
{
    return (cat_t*)malloc(sizeof(cat_t));
}

void CatInit(cat_t* cat, const char* const name)
{
    /* вызов функции родительского класса + восходящее приведение к родительскому классу */
    AnimalInit((struct animal_t*)cat, name);

    /* переопределение функции базового класса */
    cat->animal.sound = &CatSound;
}

void CatDeinit(cat_t* cat)
{
    AnimalDeinit((struct animal_t*)cat);
}

