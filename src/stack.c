#include "stack.h"

void setMaxMinV(Vvalue *Vflag, Data *arr) {
  if (arr[0].DValue > Vflag->X.Max) {
    Vflag->X.Max = arr[0].DValue;
  } else if (arr[0].DValue < Vflag->X.Min) {
    Vflag->X.Min = arr[0].DValue;
  }

  if (arr[1].DValue > Vflag->Y.Max) {
    Vflag->Y.Max = arr[1].DValue;
  } else if (arr[1].DValue < Vflag->Y.Min) {
    Vflag->Y.Min = arr[1].DValue;
  }

  if (arr[2].DValue > Vflag->Z.Max) {
    Vflag->Z.Max = arr[2].DValue;
  } else if (arr[2].DValue < Vflag->Z.Min) {
    Vflag->Z.Min = arr[2].DValue;
  }
}

Vvalue VvalueConstruct() {
  Vvalue src;
  src.X.Min = 0;
  src.X.Max = 0;
  src.Y.Min = 0;
  src.Y.Max = 0;
  src.Z.Min = 0;
  src.Z.Max = 0;
  return src;
}

void printVflags(Vvalue src) {
  printf("{x, %lf, %lf}, {y, %lf, %lf}, {z, %lf, %lf}", src.X.Max, src.X.Min,
         src.Y.Max, src.Y.Min, src.Z.Max, src.Z.Min);
  printf("\n");
}

//  NEED CLEAN RETURNED VALUE
Data *reverseString(Data *arr, int len) {
  Data *reverse = malloc(sizeof(Data) * len);
  for (int i = 0; i < len; ++i) {
    reverse[i] = arr[len - i - 1];
  }
  return reverse;
}

//  NEED CLEAN RETURNED VALUE
Data *getAllValue(Stack_t **head, int *len) {
  Data *result = NULL;
  Data *buffer = NULL;
  Data *popi = NULL;
  int stackSize = getStackSize(*head);
  int resultLen = 1;
  for (int i = 0; i < stackSize; ++i) {
    result = realloc(result, sizeof(Data) * (*head)->len * (resultLen));
    int bufferLen = (*head)->len;
    buffer = StackPop(head);
    popi = reverseString(buffer, bufferLen);
    for (int j = 0; j < bufferLen; ++j) {
      result[resultLen - 1] = popi[j];
      resultLen++;
    }
    free(buffer);
    free(popi);
  }
  popi = reverseString(result, --resultLen);
  *len = resultLen;
  free(result);
  return popi;
}

int getDatatype(Data *src) {
  if (src->switcher == IsDOUBLE) {
    return IsDOUBLE;
  }
  return IsINT;
}

void DataDPush(Data *src, double a) {
  src->switcher = IsDOUBLE;
  src->DValue = a;
  src->IValue = 0;
}

void DataIPush(Data *src, int a) {
  src->switcher = IsINT;
  src->IValue = a;
  src->DValue = 0;
}

Data *ElementCopy(Stack_t *head) {
  Data *buffer = malloc(sizeof(Data) * head->len);
  for (int i = 0; i < head->len; ++i) {
    buffer[i] = head->value[i];
  }
  return buffer;
}

//  ADD NEW ELEMENT
void StackPush(Stack_t **head, Data *arg, int len) {
  Stack_t *tmp = (Stack_t *)malloc(sizeof(Stack_t));
  tmp->len = len;
  tmp->value = (Data *)malloc(sizeof(Data) * tmp->len);
  for (int i = 0; i < tmp->len; ++i) {
    tmp->value[i] = arg[i];
  }
  tmp->next = (*head);
  (*head) = tmp;
}

//  DELETE AND RETURN TOP ELEMENT
Data *StackPop(Stack_t **head) {
  Stack_t *prev = NULL;
  Data *val;
  if (head == NULL) {
    exit(STACK_UNDERFLOW);
  }
  val = ElementCopy(*head);
  prev = (*head);
  free(prev->value);
  (*head) = (*head)->next;
  free(prev);
  return val;
}

//  PRINT NOD
void printStack(const Stack_t *head) {
  printf("Stack -> ");
  while (head) {
    printf("[ ");
    for (int i = 0; i < head->len; ++i) {
      getDatatype(head->value) == IsDOUBLE
          ? printf("%lf ", head->value[i].DValue)
          : printf("%d ", head->value[i].IValue);
    }
    printf("]\n");
    head = head->next;
  }
  printf("\n");
}

//  GET SIZE
int getStackSize(const Stack_t *head) {
  int len = 0;
  while (head) {
    head = head->next;
    len++;
  }
  return len;
}

//  DELETE ALL NODE
void StackDelete(Stack_t **head) {
  Stack_t *prev = NULL;
  int len = getStackSize(*head);
  for (int i = 0; i < len; i++) {
    free((*head)->value);
    if (*head == NULL) {
      break;
    }
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
  }
  // free(*head);
}

// https://learnc.info/adt/linked_list.html