#include "parce.h"

#include <stdio.h>

#include "MyString.h"
#include "stack.h"

//  NEED CLEAN RETURNED VALUE
double *getDataDouble(Data *src, int len) {
  double *buffer = malloc(sizeof(double) * len);
  for (int i = 0; i < len; ++i) {
    buffer[i] = src[i].DValue;
  }
  return buffer;
}

//  NEED CLEAN RETURNED VALUE
unsigned int *getDataInt(Data *src, int len) {
  unsigned int *buffer = malloc(sizeof(unsigned int) * len);
  for (int i = 0; i < len; ++i) {
    buffer[i] = src[i].IValue;
  }
  return buffer;
}

int inNum(char smb) {
  if (smb >= '0' && smb <= '9') {
    return 1;
  }
  return 0;
}

Data *getVElement(const char *fileString) {
  EString_t *string = EString();
  Data *returnData = malloc(sizeof(Data) * 1);
  int Varg = 0;
  for (int i = 0; fileString[i] != '\0'; ++i) {
    if (inNum(fileString[i]) || fileString[i] == '-' || fileString[i] == '.') {
      EStringPushElement(string, fileString[i]);
    } else if (fileString[i] == ' ' && getEStringSize(*string) != 0) {
      DataDPush(&returnData[Varg], atof(string->value));
      Varg += 1;
      returnData = realloc(returnData, sizeof(Data) * (Varg + 1));
      EStringZero(string);
    }
  }
  if (getEStringSize(*string) != 0) {
    DataDPush(&returnData[Varg], atof(string->value));
    Varg += 1;
  }
  EStringClean(string);
  if (Varg == 3) {
    return returnData;
  }
  free(returnData);
  return NULL;
}

Data *flagFsummer(Data *arr, int len) {
  int newLen = len * 2;
  int bufferCount = 1;
  Data *buffer = (Data *)calloc(sizeof(Data), newLen);
  buffer[0] = arr[0];
  for (int i = 1; i < len; ++i) {
    buffer[bufferCount] = arr[i];
    bufferCount++;
    buffer[bufferCount] = arr[i];
    bufferCount++;
  }
  buffer[bufferCount] = arr[0];
  return buffer;
}

int serchSymbol(const char *String, const char smb) {
  while (*String) {
    if (*String == smb) return 1;
    *String++;
  }
  return 0;
}

Data *categorizedStick(char *fileString, int *len) {
  EString_t *string = EString();
  Data *bufferData = malloc(sizeof(Data) * 1);
  int Farg = 0;
  int correctCount = 0;
  for (int i = 0; fileString[i] != '\0'; ++i) {
    if (correctCount > 0 && fileString[i] != ' ') {
      continue;
    }
    correctCount = 0;
    if (inNum(fileString[i])) {
      EStringPushElement(string, fileString[i]);
    } else if (fileString[i] == '/' && getEStringSize(*string) != 0) {
      DataIPush(&bufferData[Farg], atoi(string->value) - 1);
      Farg += 1;
      bufferData = realloc(bufferData, sizeof(Data) * (Farg + 1));
      EStringZero(string);
      correctCount = 1;
    }
  }
  EStringClean(string);
  Data *returnData = flagFsummer(bufferData, Farg);
  free(bufferData);
  *len = Farg * 2;
  return returnData;
}

Data *categorizedNoneStick(char *fileString, int *len) {
  EString_t *string = EString();
  Data *bufferData = malloc(sizeof(Data) * 1);
  int Farg = 0;
  for (int i = 0; fileString[i] != '\0'; ++i) {
    if (inNum(fileString[i])) {
      EStringPushElement(string, fileString[i]);
    } else if (fileString[i] == ' ' && getEStringSize(*string) != 0) {
      DataIPush(&bufferData[Farg], atoi(string->value) - 1);
      Farg += 1;
      bufferData = realloc(bufferData, sizeof(Data) * (Farg + 1));
      EStringZero(string);
    }
  }
  if (getEStringSize(*string) != 0) {
    DataIPush(&bufferData[Farg], atoi(string->value) - 1);
    Farg += 1;
    bufferData = realloc(bufferData, sizeof(Data) * (Farg + 1));
    EStringZero(string);
  }
  EStringClean(string);
  Data *returnData = flagFsummer(bufferData, Farg);
  free(bufferData);
  *len = Farg * 2;
  return returnData;
}

Data *getFElement(char *fileString, int *len) {
  if (serchSymbol(fileString, '/')) {
    return categorizedStick(fileString, len);
  } else {
    return categorizedNoneStick(fileString, len);
  }
  return NULL;
}

int parsingFile(char *fileName, Stack_t **Vvertex, Stack_t **Fvertex,
                Vvalue *Vflags) {
  FILE *objFile = NULL;
  Data *coreData = NULL;
  int res = 0;
  if ((objFile = fopen(fileName, "r")) == NULL) return FILE_NOT_EXIST;
  char buffer[512] = {0};
  fgets(buffer, 512, objFile);
  do {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      coreData = getVElement(buffer);
      if (coreData != NULL) {
        StackPush(Vvertex, coreData, NUMBER_OF_FLAGS_V);
        setMaxMinV(Vflags, coreData);
        free(coreData);
      }
    }
    if (buffer[0] == 'f' && buffer[1] == ' ') {
      int len = 0;
      coreData = getFElement(buffer, &len);
      StackPush(Fvertex, coreData, len);
      free(coreData);
    }
    coreData = NULL;
  } while ((fgets(buffer, 512, objFile)) != NULL);
  fclose(objFile);
  return res;
}
