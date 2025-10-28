#ifndef arbtirary_precision_h
#define arbtirary_precision_h

typedef struct singleDigit{
    struct singleDigit* nextNode;
    short int value;
} singleDigit;

typedef struct headerNodeDigits{
    unsigned int length;
    singleDigit* firstValue;
} headerNodeDigits;

headerNodeDigits* createLL();
void FreeLL(headerNodeDigits* head);
void printValues(headerNodeDigits* head);

#endif