//
// Created by Shafi Haque on 4/27/17.
//
# ifdef _INSTRUMENTED
# define SWAP (x , y ) { uint32_t t = x ; x = y ; y = x ; ; moveCount += 3; }
# else
# define SWAP(x , y ) { uint32_t t = x ; x = y ; y = t ; ; }
# endif
#include "bubblesort.h"
#include <stdlib.h>
#include <stdio.h>


extern uint32_t moves;
extern uint32_t compares;
//Professor Darrell Long gave us the pseudocode for this sort.
void bubbleSort(uint32_t a[], uint32_t length)
{
    uint32_t n = length;//The length is the n.
    while (n != 0)// While the n is not 0.
    {
        for (uint32_t i = 1; i <= n - 1; i++)
        {
            if (a[i - 1] > a[i])//If the left element is greater than the right element swap.
            {
                compares++;
                SWAP(a[i - 1], a[i]);//swaps the left and the right element.
                moves+=3;
            }
        }
        n = n - 1;//Decrements n
    }
    return;
}
