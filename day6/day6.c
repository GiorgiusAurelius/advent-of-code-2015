#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIGHT_GRID_EDGE 1000
#define MAX_LINE_LENGTH 100
#define SEPARATOR " "
#define MAX_LINE_TOKENS 5
#define MAX_TOKEN_LENGTH 10

typedef enum {false, true} bool;
typedef enum {TOGGLE, TURN_OFF, TURN_ON} inst;

void split_inst_line(char* in_line, char** tokens) {
  char* token;
  token = strtok(in_line, SEPARATOR);

  for (int i = 0; i < MAX_LINE_TOKENS || token != NULL; ++i) {
    tokens[i] = token;
    token = strtok(NULL, SEPARATOR);
  }
}

void first_part_solver(FILE* input, int** lights) {
  
  int lights_on = 0;
  inst curr_inst;
  char* curr_in_line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  
  char** line_tokens;
  line_tokens = malloc(sizeof(char*) * MAX_LINE_TOKENS);
  for (int i = 0; i < MAX_LINE_TOKENS; ++i) {
    line_tokens[i] = malloc(sizeof(char*) * MAX_TOKEN_LENGTH);
  }
 
  while (fgets(curr_in_line, MAX_LINE_LENGTH, input) != NULL) {
    //printf("Curr line: %s\n", curr_in_line);
    split_inst_line(curr_in_line, line_tokens);
    /*for (int i = 0; i < MAX_LINE_TOKENS; ++i) {
      printf("Token %d: %s\n", i, line_tokens[i]);
    }*/
  }

  free(curr_in_line);
  free(line_tokens);

  return;
}

void second_part_solver(FILE* input, int** lights) {
  
  return;
}

int main() {

  bool first_part = true;

  FILE* input;
  char* input_path = "/home/diego/CProjects/advent-of-code-2015/day6/input.txt";

  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error in opening the input file. The program ends.\n");
    return EXIT_FAILURE;
  }

  // Define and initialize light grid matrix
  int** light_grid;
  light_grid = malloc(sizeof(int*) * LIGHT_GRID_EDGE);
  for (int i = 0; i < LIGHT_GRID_EDGE; ++i) {
    light_grid[i] = malloc(sizeof(int*) * LIGHT_GRID_EDGE);
  }
  for (int i = 0; i < LIGHT_GRID_EDGE; ++i) {
    for (int j = 0; j < LIGHT_GRID_EDGE; ++j) {
      light_grid[i][j] = 0;
    }
  }

  if (first_part) {
    //printf("Solving first riddle's part!\n");
    first_part_solver(input, light_grid);
  } else {
    second_part_solver(input, light_grid);
  }

  free(light_grid);
  fclose(input);

  return EXIT_SUCCESS;
}