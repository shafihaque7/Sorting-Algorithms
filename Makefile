CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = sorting.o minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o

.PHONY: all
all: sorting

sorting: $(OBJECTS)
	$(CC) $(OBJECTS) -o sorting

minsort.o: minsort.c
	$(CC)  -c minsort.c -o minsort.o

bubblesort.o: bubblesort.c
	$(CC)  -c bubblesort.c -o bubblesort.o

insertionsort.o: insertionsort.c
	$(CC)  -c insertionsort.c -o insertionsort.o

quicksort.o: quicksort.c
	$(CC)  -c quicksort.c -o quicksort.o

mergesort.o: mergesort.c
	$(CC)  -c mergesort.c -o mergesort.o

sorting.o: sorting.c
	$(CC)  -c sorting.c -o sorting.o


.PHONY: clean
clean:
	rm -f $(OBJECTS) sorting
