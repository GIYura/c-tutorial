#ifndef CAT_H
#define CAT_H

/*
NOTE: дочерний класс.
*/

/* forward declaration */
struct cat_t;

/*
@brief: Create cat (allocate memory)
@in: none
@out: struct cat_t*
*/
struct cat_t* CatCreate(void);

/*
@brief: Init cat
@in: struct cat_t*
@in: char* name - cat name
@out: none
*/
void CatInit(struct cat_t* cat, const char* const name);

/*
@brief: Deinit cati
@in: struct cat_t*
@out: none
*/
void CatDeinit(struct cat_t* cat);

#endif /* CAT_H */

