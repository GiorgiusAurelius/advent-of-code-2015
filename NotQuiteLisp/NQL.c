// First problem of the AdventOfCode 2015's puzzles

//========== LIBRARIES ==========// 
#include <stdio.h>

//========== GLOBAL VARIABLES ==========//
#define UP_TOKEN '('
#define DOWN_TOKEN ')'

typedef enum { false, true } bool;

void main(){

  //========== VARIABLES DECLARATIONS ==========// 

  // Create a pointer to the input file of the program
  FILE *input;
  // Path o the input file
  char file_path[] = "/home/diego/CProjects/AdventOfCode2015/NotQuiteLisp/input.txt";
  int floor = 0;
  char direction_token;
  int num_token = 0;
  int first_time_basement;
  bool basement_reached = false;

  //========== MAIN PROGRAM BODY ==========// 
  
  // Open the input
  if ((input = fopen(file_path, "r")) != NULL) { 
    printf("The input file has been opened correctly in reading mode.\n");
  } else {
    printf("The file doesn't exist. Check the correctness of the path you provided!\n");  
  }

  // Read characters from the input file until the EOF is reached
  while ((direction_token = fgetc(input)) != EOF) {

    switch (direction_token) {
      case UP_TOKEN:
        floor++;
        break;
      case DOWN_TOKEN:
        floor--;
        break;
      default: 
        printf("The read character isn't a known direction. Got: %c.\n", direction_token); 
    }
    
    num_token++;
    if (floor < 0 && !basement_reached) {
      first_time_basement = num_token;
      basement_reached = true;
    }
  }

  printf("All the directions has been read properly. Santa reached floor: %d.\n", floor);
  printf("Following all the given directions,\n");
  printf("Santa reached the basement for the first time after: %d.\n", first_time_basement);
  fclose(input);

  return;
}