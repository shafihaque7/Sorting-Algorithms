//
// Created by Shafi Haque on 4/27/17.
//
# ifdef _INSTRUMENTED
# define SWAP (x , y ) { uint32_t t = x ; x = y ; y = x ; ; moveCount += 3; }
# else
# define SWAP(x , y ) { uint32_t t = x ; x = y ; y = t ; ; }
# endif
#include "quicksort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern uint32_t moves;
extern uint32_t compares;

//The pseudocode for quicksort was taken from https://www.youtube.com/watch?v=MZaf_9IZCrc youtube video.


void quickSort0(uint32_t arr[], int a, int b)
{
    if (a>=b)//If the first element position is greater than or equal to the last element position then it return.
    {
        return;
    }


    uint32_t pivot = arr[b];//The pivot is the last element.
    int i = a - 1, j = a;//i starts before the first element position. j starts at the first element.
    while(j<b)//while j is before the last element position.
    {

        while (arr[j] > pivot)//While the j element is greater than the pivot.
        {
            compares++;
            j++;//Increment the j.
        }
        if (arr[j] < pivot)//If the j element is less than pivot
        {
            compares++;
            i++;//increment i.

            SWAP(arr[i], arr[j]);//swap the element of i and j.
            moves+=3;

        }
        j++;//increment j.
    }

    SWAP(arr[i+1],arr[b]);//Swaps the pivot element with i+1. Since we start b as the last element.
    moves+=3;

    quickSort0(arr, a, i );//Recursively quicksorting the left side of the pivot.
    quickSort0(arr, i+2 , b);//Recursively quicksorting the right side of the pivot.
}
void quickSort(uint32_t arr[], uint32_t len)
{
    quickSort0(arr, 0, len - 1);//quicksort method pass the first 0 and then the last.
}
