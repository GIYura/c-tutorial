#include <stdio.h>
#include <stdlib.h>

#include "animal.h"
#include "cat.h"
#include "dog.h"

int main(int argc, char* argv[])
{
    struct animal_t* m_animal = AnimalCreate();
    struct cat_t* m_cat = CatCreate();
    struct dog_t* m_dog = DogCreate();

    AnimalInit(m_animal, "Mammal");
    CatInit(m_cat, "Milka");
    DogInit(m_dog, "Jack");

    AnimalSound(m_animal);
    AnimalSound((struct animal_t*)m_cat);
    AnimalSound((struct animal_t*)m_dog);

    AnimalDeinit(m_animal);
    CatDeinit(m_cat);
    DogDeinit(m_dog);

    free(m_animal);
    free(m_cat);
    free(m_dog);

    return 0;
}
