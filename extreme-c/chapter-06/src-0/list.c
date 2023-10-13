#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

typedef struct
{
    int size;
    int* buffer;
} list_t;

static int m_buffer[BUFFER_SIZE];

static bool ListIsFull(const list_t* const list)
{
    return (list->size == BUFFER_SIZE);
}

bool ListIsIndexValid(const list_t* const list, int index)
{
    return (index >= 0 && index <= list->size);
}

list_t* ListCreate(void)
{
    return (list_t*)malloc(sizeof(list_t));
}

void ListInit(list_t* const list)
{
    assert(list);

    list->size = 0;
    list->buffer = m_buffer;
}

void ListPrint(const list_t* const list)
{
    assert(list);

    printf("List: ");
    for (int i = 0; i < list->size; i++)
    {
        printf("%d ", list->buffer[i]);
    }
    printf("\n");
}

bool ListAdd(list_t* const list, int item)
{
    assert(list);

    if (ListIsFull(list))
        return false;
    
    list->buffer[list->size++] = item;
    return true;
}

bool ListGetByIndex(const list_t* const list, int index, int* const item)
{
    assert(list);

    if (!ListIsIndexValid(list, index))
    {
        printf("Index invalid\n");
        return false;
    }

    *item = list->buffer[index];
    return true;
}

int ListSize(const list_t* const list)
{
    assert(list);

    return list->size;
}

void ListClear(list_t* const list)
{
    assert(list);

    list->size = 0;
}

