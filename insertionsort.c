//
// Created by Shafi Haque on 4/27/17.
//
# ifdef _INSTRUMENTED
# define SWAP (x , y ) { uint32_t t = x ; x = y ; y = x ; ; moveCount += 3; }
# else
# define SWAP(x , y ) { uint32_t t = x ; x = y ; y = t ; ; }
# endif
#include "insertionsort.h"
#include <stdlib.h>
#include <stdio.h>


extern uint32_t moves;
extern uint32_t compares;


//The pseudocode for insertionsort was given by professor Darrell Long.
void insertionSort(uint32_t a[], uint32_t length)
{
    for (uint32_t i =1; i<length; i++)
    {
        uint32_t tmp = a[i];//The temp is used for the insertion.
        int j=i-1;
        while(j>=0 && a[j]> tmp)
        {
            compares++;
            a[j+1]=a[j];//It moves the j+1
            moves++;
            j=j-1;
        }
        a[j+1]=tmp;//A[j+1] becomes temp from the top
        moves++;
    }

    return;
}
