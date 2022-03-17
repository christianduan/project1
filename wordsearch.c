#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void cap(char* word);
void printPath(int** arr_out);
void printChop(int arr_out_num);
int bSize;
int wSize = 0;
void pathDeletion(int** arr_out, int firstI, int firstJ);
bool letterFinder(char** arr, char* word, int tally, int i, int j, int** arr_out, int first);
bool wordFinder(char** arr, char* word, int** arr_out);

// Main function, DO NOT MODIFY
int main(int argc, char **argv){
    if (argc != 2){
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL){
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char **)malloc(bSize * sizeof(char *));
    char *word = (char *)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for (i = 0; i < bSize; i++){
        *(block + i) = (char *)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j){
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

void printPuzzle(char** arr){                                   
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void word_size(char* word){
    while(*(word + wSize) != '\0'){
        wSize++;
    }
}

// Capitalizes the lowercase letters in the word that needs to be found
void cap(char* word){
    for(int i = 0; i < wSize; i++){
        if(*(word + i) >= 'a' && *(word + i) <= 'z'){
            *(word + i) = *(word + i) - 32;
        }
    }
}

// Concatenates multiple instances of repeating letters
void printChop(int arr_out_num){
    int order = 0;
    int temp = arr_out_num;

    while(temp > 0){
        temp /= 10;
        order++;
    }

    printf("%d", arr_out_num);
    printf("\t");
}

// Appends to the empty pathDeletion function to create a matrix that has the path
void printPath(int** arr_out){
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){

            if (*(*(arr_out + i) + j) == 0){
                printf("0");
                printf("\t");
            }
            else{
                printChop(*(*(arr_out + i) + j));
            }
        }
        printf("\n");
    }
}

// Empty matrix of zeros to append path to
void pathDeletion(int** arr_out, int starti, int startj){
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            if (starti != i || startj != j){
                *(*(arr_out + i) + j) = 0;
            }
        }
    }
}

// Searches surrounding letters around the indexed letter
bool letterFinder(char** arr, char* word, int tally, int i, int j, int** arr_out, int first){
    int wordIndex = bSize - 1;

    if (i > wordIndex || j > wordIndex){
        return false;
    }

    if (*(word + tally) != *(*(arr + i) + j)){
        return false;
    }

    if (strlen(word) == tally + 1){
        *(*(arr_out + i) + j) = *(*(arr_out + i) + j) * 10 + tally + 1;
        return true;
    }

    *(*(arr_out + i) + j) = *(*(arr_out + i) + j) * 10 + tally + 1;


    if (i > 0){
        if (letterFinder(arr, word, tally + 1, i - 1, j, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (i > 0 && j > 0){
        if (letterFinder(arr, word, tally + 1, i - 1, j - 1, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (j < wordIndex){
        if (letterFinder(arr, word, tally + 1, i, j - 1, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (j > 0 && i < wordIndex){
        if (letterFinder(arr, word, tally + 1, i + 1, j - 1, arr_out, 0)){
            return true;
        }
        if(first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (i < wordIndex){
        if (letterFinder(arr, word, tally + 1, i + 1, j, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (i > 0 && j > 0){
        if (letterFinder(arr, word, tally + 1, i - 1, j + 1, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (j > 0){
        if (letterFinder(arr, word, tally + 1, i, j + 1, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }

    if (j > 0 && i < wordIndex){
        if (letterFinder(arr, word, tally + 1, i + 1, j + 1, arr_out, 0)){
            return true;
        }
        if (first == true){
            pathDeletion(arr_out, i, j);
        }
    }
    
    // if (i > 0 && j > 0){
    //     if(*(*(arr + i-1)+j-1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i-1, j-1, tally+1);
    //         return true;
    //     }
    // }

    // if (i > 0){
    //     if(*(*(arr + i-1)+j) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i-1, j, tally+1);return true;
    //     }
    // }
                
    // if (i > 0 && j < bSize - 1){
    //     if(*(*(arr + i-1)+j+1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i-1, j+1, tally+1);return true;
    //     }
    // }
                
    // if(j > 0){
    //     if(*(*(arr + i)+j-1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i, j-1, tally+1);return true;
    //     }
    // }

                
    // if (j < bSize - 1){
    //     if(*(*(arr + i)+j+1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i, j+1, tally+1);return true;
    //     }
    // }
                
    // if (i < bSize && j > 0){
    //     if(*(*(arr + i+1)+j-1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i+1, j-1, tally+1);return true;
    //     }
    // }
                
    // if (i < bSize-1){
    //     if(*(*(arr + i+1)+j) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i+1, j, tally+1);return true;
    //         }
    // }
                
    // if (i < bSize-1 && j < bSize-1){
    //     if(*(*(arr + i+1)+j+1) == *(word+tally)){
    //         adjacent(arr, word, arr_out, i+1, j+1, tally+1);return true;
    //     }
    // }

    return false;
}

// Recurvisely calls the letter finder function to find the word
bool wordFinder(char** arr, char* word, int** arr_out){
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            if (letterFinder(arr, word, 0, i, j, arr_out, 1) == true){
                return true;
            }
            for (int i = 0; i < bSize; i++){
                for (int j = 0; j < bSize; j++){
                    *(*(arr_out + i) + j) = 0;
                }
            }
        }
    }

    return false;
}

void searchPuzzle(char** arr, char* word){
    cap(word);

    int** arr_out = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++){
        *(arr_out + i) = (int *)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++){
            *(*(arr_out + i) + j) = 0;
        }
    }

    if (wordFinder(arr, word, arr_out) == true){
        printf("\nWord found!\n");
        printf("Printing the search path: \n");

        printPath(arr_out);
    }
    else{
        printf("\nWord not found!\n");
    }
}
