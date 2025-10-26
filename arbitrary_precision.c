#include <stdio.h>
#include <stdlib.h>

typedef struct singleDigit{
    struct singleDigit* nextNode;
    short int value;
} singleDigit;

typedef struct headerNodeDigits{
    unsigned int length;
    singleDigit* firstValue;
} headerNodeDigits;

headerNodeDigits* createLL(){
    headerNodeDigits* temporary = (headerNodeDigits*) malloc(sizeof(headerNodeDigits));
    if(temporary != NULL){
        temporary->firstValue = NULL;
        temporary->length=0;
        return temporary;
    }
    else{
        printf("Out of memory!");
        return NULL;
    }
}

void FreeLL(headerNodeDigits* head){
    if(head == NULL || head->length == 0) return;
    else{
        singleDigit* values = head->firstValue;
        while(values != NULL){
            singleDigit* valueClean = values;
            values = values->nextNode;
            free(valueClean);
        }
        free(head);
    }
    return;
}

void printValues(headerNodeDigits* head){
    if(head == NULL || head->length == 0) return;
    else{
        singleDigit* node = head->firstValue;
        while(node != NULL){
            printf("%d",node->value);
            node = node->nextNode;
        }
    }
    return;
}

int main(){
    headerNodeDigits* value1 = createLL();
    headerNodeDigits* value2 = createLL();
    if(!value1 || !value2) return 1;
    headerNodeDigits* listOfValues[] = {value1,value2};
    for(int i=0; i<2;i++){
        int value=0;
        int length = 0;
        while(value>=0){
            singleDigit* lastDigit;
            printf("Input the digit [0-9] of the %dst value (-1 to exit): ",i+1);
            scanf("%d",&value);
            if(value >= 0 && value <10) {
                length++;
                if(listOfValues[i]->firstValue == NULL){
                    lastDigit = (singleDigit*) malloc(sizeof(singleDigit));
                    if(lastDigit == NULL) {
                        return 1;
                    }
                    else{
                        lastDigit->nextNode = NULL;
                        lastDigit->value = value;
                        listOfValues[i]->firstValue = lastDigit;\
                    }
                }
                else{
                    singleDigit* var = (singleDigit*) malloc(sizeof(singleDigit));
                    if(var == NULL){
                        return 1;
                    }
                    else{
                    var->nextNode = NULL;
                    var->value = value;
                    lastDigit->nextNode = var;
                    lastDigit = var;
                    }
                }

            }
            else if(value > 9){
                printf("Input not valid\n");
            }
        }
        listOfValues[i]->length = length;
    }

    for(int i =0 ; i<2; i++){
     printf("\nvalue %d with %d digits: ", i+1,listOfValues[i]->length);
     printValues(listOfValues[i]);
    }



    for(int i =0 ; i<2; i++){
     FreeLL(listOfValues[i]);
    }

    return 0;
}