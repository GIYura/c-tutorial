#ifndef ANIMAL_P_H
#define ANIMAL_P_H

/*
NOTE: это приватная часть родительского класса.
Она необходима чтобы иметь возможность объявить 
переменную типа animal_t в дочернем классе.
*/

/* указатель на функцию, которая является полиморфной.
Она будет переопределена в дочерних классах. */
typedef void (*OnSound_t)(void*);

typedef struct
{
    char* name;
    OnSound_t sound;
} animal_t;

#endif /* ANIMAL_P_H */
