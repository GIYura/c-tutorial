#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

/* forward declaration */
struct list_t;

/*
@brief: Create list control structure
@in: none
@out: struct list_t* - pointer to list
*/
struct list_t* ListCreate(void);

/*
@brief: Init list
@in: pointer to the list struct
@out: none
*/
void ListInit(struct list_t* const list);

/*
@brief: Print list
@in: pointer to list struct
@out: none
*/
void ListPrint(const struct list_t* const list);

/*
@brief: Add an item to the list
@in: pointer to the list struct
@in: item to be stored
@out: true - success; false - otherwise
*/
bool ListAdd(struct list_t* const list, int item);

/*
@brief: Retrieve an item by index
@in: pointer to the list struct
@in: index of the desired item
@in: item to be stored
@out: true - success; false - otherwise
*/
bool ListGetByIndex(const struct list_t* const list, int index, int* const item);

/*
@brief: Get list size
@in: pointer to the list struct
@out: number of stored items
*/
int ListSize(const struct list_t* const list);

/*
@brief: Clear the list
@in: pointer to the list struct
@out: none
*/
void ListClear(struct list_t* const list);

#endif /* LIST_H */

