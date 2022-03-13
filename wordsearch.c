#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int wSize = 0;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void word_size(char* word){
    while(*(word + wSize) != '\0'){
        wSize++;
    }
}

void cap(char* word){
    for(int i = 0; i < wSize; i++){
        if(*(word + i) >= 'a' && *(word + i) <= 'z'){
            *(word + i) = *(word + i) - 32;
        }
    }
}

void findLetter(char** arr, char* word, int** arr_out, int i, int j, int tally){
    if(*(*(arr + i)+j) == *(word+i) && *(*(arr_out + i)+j) == 0){
        *(*(arr_out+i)+j) = tally + 1;
            tally++;
    }

    else if(*(*(arr + i)+j) == *(word+i) && *(*(arr_out + i)+j) > 0){
        int temp = *(*(arr_out+i)+j);
        int new = (tally+1);
        do{
            temp = temp/10;
            new = new*10;
        }
        while (temp > 0);

        int input = new + *(*(arr_out+i)+j);

        *(*(arr_out+i)+j) = input;

        tally++;
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    int tally = 0;

    word_size(word);

    // make copy of array to output position
    int **arr_out = (int **)malloc(bSize * sizeof(int*));
    for(int i = 0; i < bSize; i++){
        *(arr_out + i) = (int*)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize - 1; ++j){
            *(*(arr_out + i)+j) = 0;
        }
    }   
    
    // capitalize word
    cap(word);
    
    // find poition of the letters in word
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(*(*(arr + i)+j) == *(word+i)){
                findLetter(arr, word, arr_out, i, j, tally);

                do{

                }
                while (*(word+tally) < wSize);
            }

            else{
                printf("Word not found!");
            }
        }
    }
   

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr_out + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}