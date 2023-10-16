#ifndef FUNC_H
#define FUNC_H

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

typedef int32_t (*handler_t)(void);

int32_t NextEvenNumber(void);

int32_t CalcFactorial(handler_t handler);

bool RandomBoolean(void);

#endif /* FUNC_H */


