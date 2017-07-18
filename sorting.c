#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>//I used memcpy.
#include "minsort.h"//Importing all the sorting header files
#include "bv.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"

#define DEFAULT_MAX_NUMBER (100) //The default max number is 100. It's at the top, because I can change it easily.
#define DEFAULT_RANDOM_SEED (8062022)//The default seed is 8062022. Again it can be changed from the top.
uint32_t moves=0;//Initializes the number of moves. I used extern on the each of the sortingalgorithm.c to have it be used for all of them.
uint32_t compares=0;//Sames as the moves. This initializes at the top.

void printUsage()//Incase there are problem with the users arguments, this method is used.
{
    printf("Usage: ./sorting -A OR -m OR -b OR -i OR -q OR -M OR -p OR -r OR -n\n");//Prints what the user should type
}
int main(int argc, char *argv[])
{
    bitV *v = newVec(5);//Creates a bitvector with 5 elements.
    uint32_t option;//The options for getopt
    uint32_t maxNumber=DEFAULT_MAX_NUMBER;//Turning the top max number into a uint_32t
    uint32_t numberFlag = 0;//Initializing the number flag.
    int seed= DEFAULT_RANDOM_SEED; //Taking the random seed at the top and turning it into a seed.
    uint32_t DEFAULT_PRINT_NUMBER = 100;//The default print number is 100.
    opterr = 0;//opterr is 0 by default.
    uint32_t negativeOne=-1;//This is used since we are comparing unit with uint.

    while ((option = getopt(argc, argv, " AmbiqMp:r:n:")) != negativeOne)//getopt has all the different options.
    {
        switch (option)//Switch is used for efficiency.
        {
            case 'n'://If the argument is -n. Then the the max number is what comes after -n.
            {
                if(numberFlag)
                {
                    fprintf(stderr, "[ARGUMENT ERROR] Value for option already set {-n: %d}\n",maxNumber);//If the value is alreay set.
                    return 3;
                }
                maxNumber=atoi(optarg);//This is where it gets the max number from.
                if(maxNumber==0)// The max number cant be zero
                {
                    numberFlag =0;
                }
                else
                {
                    numberFlag=1;
                }

                break;
            }
            case 'A'://A means employ all of the algorithm.
            {
                oneVec(v);// It sets all of the bit vector to one.
                break;
            }
            case 'r':// r is used to set the random seed.
            {
                seed=atoi(optarg);//The seed becomes what comes after -r.
                //printf("\n\n\n\n\n%d",seed);
                break;
            }
            case 'p':// p is used to print the specific number of elements.
            {
                DEFAULT_PRINT_NUMBER=atoi(optarg);// It changes the default print number when the argument is -p

                break;
            }
            case 'i':// i enables insertionsort.
            {
                setBit(v,2);//If the thid bit is 1, then it enables the insertionsort.
                break;
            }
            case 'm':// m enables the minsort
            {
                setBit(v,0);//If the first bit is 0, then it enables min sort.
                break;
            }
            case 'q':
            {
                setBit(v,3);//If the fourth bit is 1 then it enables the quick sort.
                break;
            }
            case 'b':
            {
                setBit(v,1);// If the second bit is one, then it enables bubble sort.
                break;
            }
            case 'M'://Capital M means merge sort.
            {
                setBit(v,4);// Merge sort is the last bit.
                break;
            }


            case '?'://If there is a problem with the user argument or the user types in this. Then this is enabled. This is directly from Yash's example
            {
                if (optopt == 'n')
                {
                    if(numberFlag)
                    {
                        fprintf(stderr,"[ARGUEMENT ERROR] Value of option already set {-n: %d}\n\n",maxNumber);//If there is a proble with -n
                    }
                    else
                    {
                        fprintf(stderr, "[ARGUEMENT ERROR] Valie for option not supplied {-n}\n\n");
                    }
                }
                else
                {
                    fprintf(stderr, "[ARGUEMENT ERROR] Unknown option supllied {-%c}\n\n",optopt);//If the option is unknown
                }
                printUsage();


                return 1;
            }
            default:
            {
                fprintf(stderr, "[UNKNOWN ERROR] Something very bad happend\n");//Indicates that something didn't go right.
                return 2;
            }
        }
    }


    if (DEFAULT_PRINT_NUMBER>=maxNumber)//If the default print number is greater than the amount of numbers that is being sorted.
    {
        DEFAULT_PRINT_NUMBER=maxNumber;//It sets the default print number to the max number thats being sorted.
    }


    uint32_t randomNumber;//Initialized the randomNumber as an unsigned integer.
    srand(seed);//srand the seed
    uint32_t *myNumbers = malloc(maxNumber*sizeof(uint32_t));//Creates an array for the random numbers.
    for (uint32_t i = 0; i < maxNumber; i++)
    {
        randomNumber = rand() % 16777216;//%16777216 so it is 24 bits. 2 to the 24 -1
        myNumbers[i] = randomNumber;//myNumbers is the randomNumber
    }

    //minSort
    if(valBit(v,0)==1)//The first bit is the minsort.
    {
        moves=0;//Initializes the moves and compares for this sort.
        compares=0;
        uint32_t *randomNumbersForThisSort = malloc(maxNumber*sizeof(uint32_t));//Creates a new array for this specific sort
        memcpy(randomNumbersForThisSort, myNumbers, (maxNumber)*sizeof(uint32_t));//Copies whatever is on the myNumbers array.
        minSort(randomNumbersForThisSort, maxNumber);//Does the minsort method.The first argument is the array being passed. Maxnumber is the length.
        uint32_t elements=maxNumber;//The number of elements is the max number thats going to be sorted.
        printf("Min Sort\n");//Prints min sort
        printf("%d elements\n%d moves\n%d compares",elements,moves,compares);//Prints the elements, moves and compares.
        for (uint32_t i = 0; i < DEFAULT_PRINT_NUMBER; i++)
        {
            if (i%7==0){
                printf("\n");
            }
            printf("%13d", randomNumbersForThisSort[i]);//Prints whatever the print number is. By default it is one hundred.
        }
        printf("\n");
        free(randomNumbersForThisSort);// Free the randomNumbersForThisSort
        randomNumbersForThisSort=NULL;//Nulls the randomNumbersForThisSort

    }
    //bubbleSort
    if(valBit(v,1)==1)//The second bit is the bubble sort.
    {
        moves=0;//Initializes the moves and compares for this sort.
        compares=0;
        uint32_t *randomNumbersForThisSort = malloc(maxNumber*sizeof(uint32_t));//Creates a new array for this specific sort
        memcpy(randomNumbersForThisSort, myNumbers, (maxNumber)*sizeof(uint32_t));//Copies whatever is on the myNumbers array.
        bubbleSort(randomNumbersForThisSort, maxNumber);//Does the bubblesort method.The first argument is the array being passed. Maxnumber is the length.
        uint32_t elements=maxNumber;//The number of elements is the max number thats going to be sorted.
        printf("Bubble Sort\n");
        printf("%d elements\n%d moves\n%d compares",elements,moves,compares);//Prints the elements, moves and compares.
        for (uint32_t i = 0; i < DEFAULT_PRINT_NUMBER; i++)
        {
            if (i%7==0){
                printf("\n");
            }
            printf("%13d", randomNumbersForThisSort[i]);//Prints whatever the print number is. By default it is one hundred.
        }
        printf("\n");
        free(randomNumbersForThisSort);// Free the randomNumbersForThisSort
        randomNumbersForThisSort=NULL;//Nulls the randomNumbersForThisSort

    }
    if(valBit(v,2)==1)//The third bit is the insertionSort
    {
        moves=0;//Initializes the moves and compares for this sort.
        compares=0;
        uint32_t *randomNumbersForThisSort = malloc(maxNumber*sizeof(uint32_t));//Creates a new array for this specific sort
        memcpy(randomNumbersForThisSort, myNumbers, (maxNumber)*sizeof(uint32_t));//Copies whatever is on the myNumbers array.
        insertionSort(randomNumbersForThisSort, maxNumber);//Does the insertionSort method. The first argument is the array being passed. Maxnumber is the length.
        uint32_t elements=maxNumber;//The number of elements is the max number thats going to be sorted.
        printf("Insertion Sort\n");
        printf("%d elements\n%d moves\n%d compares",elements,moves,compares);//Prints the elements, moves and compares.
        for (uint32_t i = 0; i < DEFAULT_PRINT_NUMBER; i++)
        {
            if (i%7==0){
                printf("\n");
            }
            printf("%13d", randomNumbersForThisSort[i]);//Prints whatever the print number is. By default it is one hundred.
        }
        printf("\n");
        free(randomNumbersForThisSort);// Free the randomNumbersForThisSort
        randomNumbersForThisSort=NULL;//Nulls the randomNumbersForThisSort


    }
    if(valBit(v,3)==1)//The fourth bit is the quicksort.
    {
        moves=0;//Initializes the moves and compares for this sort.
        compares=0;
        uint32_t *randomNumbersForThisSort = malloc(maxNumber*sizeof(uint32_t));//Creates a new array for this specific sort
        memcpy(randomNumbersForThisSort, myNumbers, (maxNumber)*sizeof(uint32_t));//Copies whatever is on the myNumbers array.
        quickSort(randomNumbersForThisSort, maxNumber);//Does the quicksort method. The first argument is the array being passed. Maxnumber is the length.
        uint32_t elements=maxNumber;//The number of elements is the max number thats going to be sorted.
        printf("Quick Sort\n");
        printf("%d elements\n%d moves\n%d compares",elements,moves,compares);//Prints the elements, moves and compares.
        for (uint32_t i = 0; i < DEFAULT_PRINT_NUMBER; i++)
        {
            if (i%7==0){
                printf("\n");
            }
            printf("%13d", randomNumbersForThisSort[i]);//Prints whatever the print number is. By default it is one hundred.
        }
        printf("\n");
        free(randomNumbersForThisSort);// Free the randomNumbersForThisSort
        randomNumbersForThisSort=NULL;//Nulls the randomNumbersForThisSort

    }
    if(valBit(v,4)==1)//The fifth bit is the merge sort.
    {
        moves=0;//Initializes the moves and compares for this sort.
        compares=0;
        uint32_t *randomNumbersForThisSort = malloc(maxNumber*sizeof(uint32_t));//Creates a new array for this specific sort
        memcpy(randomNumbersForThisSort, myNumbers, (maxNumber)*sizeof(uint32_t));//Copies whatever is on the myNumbers array.
        mergeSort(randomNumbersForThisSort, maxNumber);//Does the mergeSort method. The first argument is the array being passed. Maxnumber is the length.
        uint32_t elements=maxNumber;//The number of elements is the max number thats going to be sorted.
        printf("Merge Sort\n");
        printf("%d elements\n%d moves\n%d compares",elements,moves,compares);//Prints the elements, moves and compares.
        for (uint32_t i = 0; i < DEFAULT_PRINT_NUMBER; i++)
        {
            if (i%7==0){
                printf("\n");
            }
            printf("%13d", randomNumbersForThisSort[i]);//Prints whatever the print number is. By default it is one hundred.
        }
        printf("\n");
        free(randomNumbersForThisSort);// Free the randomNumbersForThisSort
        randomNumbersForThisSort=NULL;//Nulls the randomNumbersForThisSort

    }
    free(myNumbers);//Frees the myNumber, which is where the random number is generated.
    myNumbers=NULL;//Nulls the myNumber
    delVec(v);//Deletes the bitvector.

    return 0;
}
