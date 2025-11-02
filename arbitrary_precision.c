#include "arbitrary_precision.h"
#include <stdio.h>
#include <stdlib.h>

headerNodeDigits *createDataStructure(Type type) {
  headerNodeDigits *temporary =
      (headerNodeDigits *)malloc(sizeof(headerNodeDigits));
  if (temporary != NULL) {
    temporary->firstNode = NULL;
    temporary->length = 0;
    temporary->type = type;
    return temporary;
  } else {
    printf("Out of memory!");
    return NULL;
  }
}

void FreeLL(headerNodeDigits *head) {
  if (head == NULL || head->length == 0)
    return;
  else {
    singleDigit *values = head->firstNode;
    while (values != NULL) {
      singleDigit *valueClean = values;
      values = values->nextNode;
      free(valueClean);
    }
    free(head);
  }
  return;
}

void printRecursively(singleDigit *node){
  if(node == NULL){
    return;
  }
  else{
    printRecursively(node->nextNode);
    printf("%d",node->value);
  }
}

void printValues(headerNodeDigits *head) {
  if (head == NULL || head->length == 0)
    return;
  else {
    singleDigit *node = head->firstNode;
    if(head->type == queue){
      while (node != NULL) {
        printf("%d", node->value);
        node = node->nextNode;
      }
    }
    else if(head->type == stack){
      printRecursively(node);
    }
  }
}

void createNode(headerNodeDigits *header, int value) {
  if (header == NULL)
    return;
  else {
    singleDigit *newNode = (singleDigit *)malloc(sizeof(singleDigit));
    if (newNode == NULL)
      return;
    singleDigit *var = header->firstNode;
    if (header->type == queue) {
      newNode->nextNode = NULL;
      newNode->value = value;
      if (var == NULL) {
        header->firstNode = newNode;
      } else {
        while (var->nextNode != NULL) {
          var = var->nextNode;
        }
        var->nextNode = newNode;
      }
    } else if (header->type == stack) {
      newNode->nextNode = var;
      newNode->value = value;
      header->firstNode = newNode;
    }
    header->length++;
  }
}


// create a a node that its data structure is stack from the sum of two digits.
singleDigit *createNodeFrom2Digits(singleDigit *value1, singleDigit *value2,
                                   int *carry, singleDigit *previousNode) {
  
  
  singleDigit *node = (singleDigit *)malloc(sizeof(singleDigit));
  if (!node)
    return NULL;
  else {
    int digit1 = (value1 == NULL)? (int) 0 : value1->value;
    int digit2 = (value2 == NULL)? (int) 0 : value2->value;
    int sum = digit1 + digit2 + *carry;
    node->nextNode = previousNode;
    node->value = sum % 10;
    *carry = sum / 10;
    return node;
  }
}

headerNodeDigits *sumValuesFromHeaders(headerNodeDigits *header1,
                                  headerNodeDigits *header2) {
  if (!header1 || !header2)
    return NULL;

  int carry = 0;

  singleDigit *current1 = header1->firstNode;
  singleDigit *current2 = header2->firstNode;
  singleDigit *prevAnswer = NULL;
  headerNodeDigits *newHeader = createDataStructure(queue);
  while (current1 != NULL || current2 != NULL || carry != 0) {
    prevAnswer = createNodeFrom2Digits(current1, current2, &carry, prevAnswer);
    newHeader->length++;
    if(current1 != NULL){
      current1 = current1->nextNode; 
    }
    if(current2 != NULL){
      current2 = current2->nextNode;
    }

  }
  newHeader->firstNode = prevAnswer;
  return newHeader;
}

int main() {
  headerNodeDigits *value1 = createDataStructure(stack);
  headerNodeDigits *value2 = createDataStructure(stack);
  
  if (!value1 || !value2)
    return 1;
  headerNodeDigits *listOfHeaders[2] = {value1,value2};
  for(int i=0;i<2;i++){
    int value = 0;
    while (value >= 0) {
      printf("Input the digit [0-9] of the %dst value (<0 to exit): ",i+1);
      scanf("%d", &value);
      if (value >= 0 && value < 10) {
        createNode(listOfHeaders[i], value);
      } else if (value > 9) {
        printf("Input not valid");
      }
    }
  }


  for (int i = 0; i < 2; i++) {
    printf("\nvalue %d with %d digits: ", i + 1, listOfHeaders[i]->length);
    printValues(listOfHeaders[i]);
  }

  fflush(stdout);

  headerNodeDigits *resultSum = sumValuesFromHeaders(listOfHeaders[0], listOfHeaders[1]);
  printf("\nResult from the sum of value 1 and value 2: ");
  printValues(resultSum);
  fflush(stdout);
  for(int i=0;i<2;i++){
    FreeLL(listOfHeaders[i]);
  }
  FreeLL(resultSum);
  return 0;
}
