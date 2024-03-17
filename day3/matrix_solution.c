//========== LIBRARIES ==========//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//========== GLOBAL VARIABLES ==========//
#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

//========== MAIN BODY ==========//
void main() {

  //========== VARIABLES DECLARATIONS ==========//
  FILE *input;
  char input_path[] = "/home/diego/CProjects/advent-of-code-2015/day3/input.txt";  
  char direction_token;

  int starting_edge = 4096;
  int **houses;
  
  houses = malloc(sizeof(int*) * starting_edge);
  for (int i = 0; i < starting_edge; ++i) {
    houses[i] = malloc(sizeof(int) * starting_edge);
  }

  //Fill the matrix
  for (int i = 0; i < starting_edge; i++) {
    for (int j = 0; j < starting_edge; j++) {
      houses[i][j] = 0;
    }
  }

  int curr_x = starting_edge / 2;
  int curr_y = starting_edge / 2;
  houses[curr_y][curr_x]++;

  int new_x, new_y;

  int houses_visited_once = 1;

  // Open input file                                                       
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when trying to open the input file. The program ends.\n");
    return;
  }

  // Read the instructions  
  while ((direction_token = fgetc(input)) != EOF) {
    switch (direction_token) {

      case NORTH:

        new_y = curr_y--;
        if (new_y < 0) {
          // Increase the size of the matrix
          printf("The matrix is too little!\n");
        } 
        curr_y--;
        houses[curr_y][curr_x]++;
        if (houses[curr_y][curr_x] == 1) {
          houses_visited_once++;
        }
        break;

      case SOUTH:

        new_y = curr_y++;
        if (new_y > starting_edge) {
          // Increase the size of the matrix
          printf("The matrix is too little!\n");
        }
        curr_y++;
        houses[curr_y][curr_x]++;
        if (houses[curr_y][curr_x] == 1) {
          houses_visited_once++;
        }
        break;

      case EAST:

        new_x = curr_x++;
        if (new_x > starting_edge) {
          // Incease the size of the matrix
          printf("The matrix is too little!\n");
        }
        curr_x++;
        houses[curr_y][curr_x]++;
        if (houses[curr_y][curr_x] == 1) {
          houses_visited_once++;
        }
        break;

      case WEST:

        new_x = curr_x--;
        if (new_x < 0) {
          // Increase the size of the matrix
          printf("The matrix is too little!\n");
        } 
        curr_x--;
        houses[curr_y][curr_x]++;
        if (houses[curr_y][curr_x] == 1) {
          houses_visited_once++;
        }
        break;

      default:
        printf("The read character isn't a valid direction. Got: %c.\n", direction_token);
        break;
    }
  }

  printf("Santa has visited %d houses at least once.\n", houses_visited_once);

  free(houses);
  fclose(input);
  return;
}
