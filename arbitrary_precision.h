#ifndef arbtirary_precision_h
#define arbtirary_precision_h

typedef struct singleDigit{
    struct singleDigit* nextNode;
    int value;
} singleDigit;

typedef enum {
    queue,
    stack
} Type;

typedef struct headerNodeDigits{
    int length;
    singleDigit* firstNode;
    Type type;   
} headerNodeDigits;

headerNodeDigits *createDataStructure(Type);
void FreeLL(headerNodeDigits*);
void printValues(headerNodeDigits*);
void createNode(headerNodeDigits*, int);
singleDigit *createNodeFrom2Digits(singleDigit*, singleDigit*, int*, singleDigit*);
headerNodeDigits *sumValuesFromHeaders(headerNodeDigits*, headerNodeDigits*);
#endif