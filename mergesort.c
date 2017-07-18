//
// Created by Shafi Haque on 4/27/17.
//
# ifdef _INSTRUMENTED
# define SWAP (x , y ) { uint32_t t = x ; x = y ; y = x ; ; moveCount += 3; }
# else
# define SWAP(x , y ) { uint32_t t = x ; x = y ; y = t ; ; }
# endif
#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>


extern uint32_t moves;
extern uint32_t compares;

//The pseudocode for this merge sort was taken from this https://www.youtube.com/watch?v=TzeBrDU-JaY video.

void merge(uint32_t L[], uint32_t R[], uint32_t A[],uint32_t leftSize,uint32_t rightSize)
{
    uint32_t leftLength = leftSize;//leftLength is length of left
    uint32_t rightLength = rightSize;//rightLength is length of right
    uint32_t i =0;//i is for incrementing the left size
    uint32_t j=0;//j is for incrementing the right size.
    uint32_t k=0;//k is for incrementing the a array.
    while(i<leftLength && j<rightLength)//If i is less than left length and j is less than right length.
    {
        if(L[i]<=R[j])//If the left element is less than the right element.
        {
            compares++;
            A[k]=L[i];//Overwriting A[k] to the left of i.
            moves++;//increments the moves
            ++k;//increment k, which is referring to the a array
            ++i;//increment i, which is referring to the left size
        }
        else
        {
            A[k]=R[j];//The main array is the right one.
            moves++;
            ++k;//incrementing the position for k
            ++j;//increment the right size.
        }
    }
    while(i<leftLength)//while the left increment which is i is less than the left length.
    {
        compares++;
        A[k]=L[i];//The array i is the element of left.
        moves++;
        ++i;//Increment the i.
        ++k;//Increment the k.
    }
    while(j<rightLength)//while j is less than the right length.
    {
        A[k]=R[j];//The A[k] is equal to the R[j]
        moves++;
        ++j;
        ++k;
    }


}
void mergeSort(uint32_t a[], uint32_t m)
{
    uint32_t n =m;
    if(n<2)
        return;
    uint32_t mid = n/2;
    uint32_t *left = malloc(mid*sizeof(uint32_t));//Creating the left array.
    uint32_t *right = malloc((n-mid)*sizeof(uint32_t));//Creating the right array.
    for (uint32_t i=0; i<=mid-1; ++i)
    {
        left[i]=a[i];//The left element is same as the a element.
        moves++;
    }
    for(uint32_t i=mid; i<=n-1;++i)
    {
        right[i-mid]=a[i];//This is making right as zero.
        moves++;
    }
    mergeSort(left,mid);//Partitions the left and mid, and recursively sorts it
    mergeSort(right,n-mid);//Partitions the right side, and recursively sorts it
    merge(left,right,a,mid,n-mid);//Merges both the left and the rigth
    free(left);//frees the left
    free(right);//frees the right
    left=NULL;//Nulls the left
    right=NULL;//Nulls the right
}
