#include "MyString.h"

EString_t *EString() {
  EString_t *myString = (EString_t *)malloc(sizeof(EString_t));
  myString->len = 0;
  myString->value = NULL;
  return myString;
}

void EStringPushElement(EString_t *myString, char smb) {
  myString->len++;
  if (myString->value == NULL) {
    myString->value = (char *)calloc(sizeof(char), myString->len);
  } else {
    myString->value = realloc(myString->value, sizeof(char) * myString->len);
  }
  myString->value[myString->len - 1] = smb;
}

void EStringZero(EString_t *myString) {
  free(myString->value);
  myString->len = 0;
  myString->value = NULL;
}

void EStringClean(EString_t *myString) {
  free(myString->value);
  myString->value = NULL;
  myString->len = 0;
  free(myString);
  myString = NULL;
}

size_t getEStringSize(EString_t myString) { return myString.len; }

char *getEStringValue(const EString_t *myString) { return myString->value; }