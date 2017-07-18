//
// Created by Shafi Haque on 4/27/17.
//
# ifdef _INSTRUMENTED
# define SWAP (x , y ) { uint32_t t = x ; x = y ; y = x ; ; moveCount += 3; }//Swaps the number
# else
# define SWAP(x , y ) { uint32_t t = x ; x = y ; y = t ; ; }
# endif
#include "minsort.h"
#include <stdlib.h>
#include <stdio.h>


extern uint32_t moves;
extern uint32_t compares;

//This was fully given to us by Professor Darrell Long.

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last)
{
    uint32_t smallest = first;//First it assumes that the first element is the least element.
    for (uint32_t i = first; i < last; i += 1)
    {
        smallest = a[i] < a[smallest] ? i : smallest;//If a[i] is less than a[smallest] then smallest is i. Else smallest doesn't change
        compares++;
    }
    return smallest;//The min index returns the smallest.
}


void minSort(uint32_t a[], uint32_t length)
{
    for (uint32_t i = 0; i < length - 1; i += 1)
    {

        uint32_t  smallest = minIndex(a,i,length);//smalest is equalt to the return of minIndex
        if (smallest != i)
        {

            SWAP(a[smallest], a[i]);//Swaps if smallest is not equal to i.
            moves+=3;

        }
    }
    return;
}
