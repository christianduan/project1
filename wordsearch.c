#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int concate(int** arr_out, int tally, int i, int j);
int bSize;
int wSize;
int **arr_out;

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

// Obtains size of word
void word_size(char* word){
    while(*(word + wSize) != '\0'){
        wSize++;
    }
}

// Capitalizes any lowercase letters
void cap(char* word){
    for(int i = 0; i < wSize; i++){
        if(*(word + i) >= 'a' && *(word + i) <= 'z'){
            *(word + i) = *(word + i) - 32;
        }
    }
}

// Concatenates repeating path to repeated letters
int concate(int** arr_out, int tally, int i, int j){
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
// Creates a bool value that is used to determine if the word is found
bool findLetter(char** arr, char* word, int tally, int i, int j, int bSize, int** arr_out){
    int wordIndex = bSize - 1;

    if(wSize == tally){
        return true;
    }

    if(i > wordIndex || j > wordIndex){
        return false;
    }

    if(*(word + tally) != *(*(arr + i) + j)){
        return false;
    }

    if(i > 0){
        if(findLetter(arr, word, tally + 1, i - 1, j, bSize, arr_out) == true){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(i > 0 && j > 0){
        if(findLetter(arr, word, tally + 1, i - 1, j - 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(j < wordIndex){
         if(findLetter(arr, word, tally + 1, i, j - 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(j > 0 && i < wordIndex){
         if(findLetter(arr, word, tally + 1, i + 1, j - 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(i < wordIndex){
         if(findLetter(arr, word, tally + 1, i + 1, j, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(i > 0 && j > 0){
         if(findLetter(arr, word, tally + 1, i - 1, j + 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(j > 0){
         if(findLetter(arr, word, tally + 1, i, j + 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
    if(j > 0 && i < wordIndex){
         if(findLetter(arr, word, tally + 1, i + 1, j + 1, bSize, arr_out)){
            if(*(*(arr_out + i) + j) == 0){
                *(*(arr_out + i) + j) = tally + 1;
            }
            else{
                *(*(arr_out + i) + j) = concate(arr_out, tally, i, j);
            }
            return true;
        }
    }
}

// Function to print out the final array
void printOut(int** arr_out){
    printf("Word found!\n");
    printf("Printing results: \n");
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%i ", *(*(arr_out + i) + j));
            printf("\t");
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    int tally = 0;

    bool found = false;

    word_size(word);
 
    // Make copy of array to output position of word's letters
    arr_out = (int **)malloc(bSize * sizeof(int*));
    for(int i = 0; i < bSize; i++){
        *(arr_out + i) = (int*)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; ++j){
            *(*(arr_out + i)+j) = 0;
        }
    }   
    
    // Capitalizes word
    cap(word);
    
    // find position of the letters in word
    for(int  i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(*(*(arr + i)+j) == *(word+tally)){
                if(findLetter(arr, word, 0, i, j, bSize, arr_out) == true){
                    found = true;
                }
                else{
                    found = false;
                }
            }
        }
}
    if (found == false){
        printf("Word not found!\n");
    }
   
    if (found == true){
        printOut(arr_out);
    }

}