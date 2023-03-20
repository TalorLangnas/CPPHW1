#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef struct AdptArray_
{    
    size_t ArrSize;
    PElement *pElementArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;

}AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC newCopyFunc, DEL_FUNC newDelFunc,PRINT_FUNC newPrintFunc){   
    // input validation
    if(newDelFunc == NULL || newCopyFunc == NULL || newPrintFunc == NULL) 
    {
        return NULL;
    }

    PAdptArray pAdptArray = (PAdptArray)malloc(sizeof(AdptArray));
    if(pAdptArray==NULL)
    {
        return NULL;
    }    
    
    pAdptArray-> delFunc = newDelFunc;
    pAdptArray-> copyFunc = newCopyFunc;
    pAdptArray-> printFunc = newPrintFunc;
    pAdptArray-> ArrSize = 1;
    pAdptArray-> pElementArr = (PElement*)calloc(1,sizeof(PElement));
    if((pAdptArray-> pElementArr)==NULL)
    {
        free(pAdptArray);
        return NULL;
    }

    return pAdptArray;
}

void DeleteAdptArray(PAdptArray pAdptArray){
    //input validation
    if(pAdptArray == NULL)
    {
         return;
    }

    for(int i=0; i< pAdptArray->ArrSize; i++)
    {
        if(pAdptArray->pElementArr[i]!=NULL)
        {
           pAdptArray->delFunc(pAdptArray->pElementArr[i]);
        }
    }
     free(pAdptArray->pElementArr);
     free(pAdptArray);
     return;
}



Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement pElement)
{   
    //input validation
    if(pAdptArray == NULL || index<0)
    {
        return FAIL;
    }
    //case 1: index isn't in the Array's range 

    if(index >= pAdptArray->ArrSize)
    {
        PElement *newPElementArr = (PElement*)realloc(pAdptArray->pElementArr,(index+1)* sizeof(PElement));
        if(newPElementArr == NULL)
        {
            return FAIL;
        }

       for(int i =pAdptArray->ArrSize; i<index+1 ; i++)
       {
            newPElementArr[i] = NULL;
       }
        pAdptArray -> ArrSize = index+1;
        pAdptArray->pElementArr = newPElementArr;
    }
    //case 2: index is in the Array's range

    else if(pAdptArray->pElementArr[index]!=NULL)
    {
         pAdptArray -> delFunc(pAdptArray->pElementArr[index]);
    }

    pAdptArray->pElementArr[index] = pAdptArray -> copyFunc(pElement);
    
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int indx){
    // input validation 
    if(pAdptArray == NULL)
    {
        return NULL;
    }
    if(indx >= pAdptArray->ArrSize)
    {
         return NULL;
    }
    if(indx < 0)
    {
        return NULL;
    }
    if(pAdptArray->pElementArr[indx] == NULL)
    {
        return NULL;
    }

    PElement cpyPelement = pAdptArray->copyFunc(pAdptArray->pElementArr[indx]);    
    
    return cpyPelement;
}

int GetAdptArraySize(PAdptArray pAdptArray){

    if(pAdptArray == NULL)
    {
        return -1;
    }
    else
    {
        return pAdptArray->ArrSize;
    }
}

void PrintDB(PAdptArray pAdptArray){
    if(pAdptArray == NULL)
    {
       return;
    }    
    for(int i=0; i<(pAdptArray->ArrSize); i++)
    {
        if(pAdptArray->pElementArr[i]!=NULL)
        {
            pAdptArray->printFunc(pAdptArray->pElementArr[i]);
        }        
    }
}

