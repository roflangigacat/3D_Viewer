#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

#define IsDOUBLE 'D'
#define IsINT 'I'

typedef struct {
  double Max;
  double Min;
} MM;

typedef struct {
  MM X;
  MM Y;
  MM Z;
} Vvalue;

Vvalue VvalueConstruct();

typedef struct {
  double DValue;
  unsigned int IValue;
  char switcher;
} Data;

typedef double *U;

typedef struct Stack {
  Data *value;
  int len;
  struct Stack *next;
} Stack_t;

// UNION DATA
void DataDPush(Data *src, double a);
void DataIPush(Data *src, int a);

// STACK
void StackPush(Stack_t **head, Data *arg, int len);
Data *StackPop(Stack_t **head);
Data *StackPeek(Stack_t *head);
void printStack(const Stack_t *head);
int getStackSize(const Stack_t *head);
void StackDelete(Stack_t **head);
void setMaxMinV(Vvalue *Vflag, Data *arr);
void printVflags(Vvalue src);
Data *reverseString(Data *arr, int len);
Data *getAllValue(Stack_t **head, int *len);
int getDatatype(Data *src);
Data *ElementCopy(Stack_t *head);

#endif  // SRC_STACK_H_
