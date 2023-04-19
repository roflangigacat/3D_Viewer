#ifndef SRC_MYSTRING_H_
#define SRC_MYSTRING_H_

#include <stdlib.h>

typedef struct EString_type {
  char *value;
  size_t len;
} EString_t;

EString_t *EString();
void EStringPushElement(EString_t *myString, char smb);
void EStringZero(EString_t *myString);
void EStringClean(EString_t *myStack);

size_t getEStringSize(EString_t myString);
char *getEStringValue(const EString_t *myString);

#endif  // SRC_MYSTRING_H_
