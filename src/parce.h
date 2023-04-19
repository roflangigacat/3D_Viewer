#ifndef SRC_PARCE_H_
#define SRC_PARCE_H_

#include <stdio.h>

#include "stack.h"

#define FILE_NOT_EXIST -103
#define NUMBER_OF_FLAGS_V 3

double *getVline(Stack_t **Vflags);
unsigned int *getFline(Stack_t **Fflags);
double *getDataDouble(Data *src, int len);
unsigned int *getDataInt(Data *src, int len);
int inNum(char smb);
int parsingFile(char *fileName, Stack_t **Vvertex, Stack_t **Fvertex,
                Vvalue *Vflags);

#endif  // SRC_PARCE_H_
