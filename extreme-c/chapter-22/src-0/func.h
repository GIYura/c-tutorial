#ifndef FUNC_H
#define FUNC_H

#include <stdint.h>
#include <unistd.h>

typedef int32_t (*handler_t)();

int32_t NextEvenNumber(void);

int32_t CalcFactorial(handler_t handler);

#endif /* FUNC_H */


