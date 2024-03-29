#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIGHT_GRID_EDGE 1000
#define MAX_LINE_LENGTH 100
#define SEPARATOR " "
#define MAX_LINE_TOKENS 5
#define MAX_TOKEN_LENGTH 10
#define NUM_SEPARATOR ','

typedef enum {false, true} bool;
typedef enum {TOGGLE, TURN_OFF, TURN_ON} inst;

// This function splits the instruction line in tokens separed by a " "
void split_instruction_line(char* in_line, char** tokens) {
  char* token;
  token = strtok(in_line, SEPARATOR);

  for (int i = 0; i < MAX_LINE_TOKENS || token != NULL; ++i) {
    tokens[i] = token;
    token = strtok(NULL, SEPARATOR);
  }
}

// This function converts the numbers in the instruction from string to integer 
void str_to_num(char* str, unsigned int* nums) {
  unsigned int curr_cypher;
  unsigned int temp = 0;

  int last_el_index = strlen(str);
  if (str[last_el_index-1] == '\n') {
    str[last_el_index-1] = '\0';
  }

  for (int i = 0; i < strlen(str); ++i) {
    if (str[i] != NUM_SEPARATOR) {
      curr_cypher = (unsigned int) str[i] - 48;
      temp = temp * 10 + curr_cypher;
    } else {
      nums[0] = temp;
      temp = 0; 
    }
  }
  nums[1] = temp;  
}

void get_affected_rnc(char* from_str, char* to_str, unsigned int** rnc_mat) {

  str_to_num(from_str, rnc_mat[0]);
  str_to_num(to_str, rnc_mat[1]);

}

// This function handles the toggle operation
int handle_toggle(unsigned int** idx_mat, int** lights) {
  int switched = 0;
  unsigned int r0 = idx_mat[0][0];
  unsigned int c0 = idx_mat[0][1];
  unsigned int r1 = idx_mat[1][0];
  unsigned int c1 = idx_mat[1][1];

  for (int i = r0; i <= r1; ++i) {
    for (int j = c0; j <= c1; ++j) {
      if (lights[i][j]) {
        //If light is on, turn off
        lights[i][j] = 0;
        --switched;
      } else {
        lights[i][j] = 1;
        ++switched;
      }      
    }
  }

  return switched;
}

// This function handles the turn OFF operation
int handle_turn_off(unsigned int** idx_mat, int** lights) {

  int switched_off = 0;
  unsigned int r0 = idx_mat[0][0];
  unsigned int c0 = idx_mat[0][1];
  unsigned int r1 = idx_mat[1][0];
  unsigned int c1 = idx_mat[1][1];

  for (int i = r0; i <= r1; ++i) {
    for (int j = c0; j <= c1; ++j) {
      if (lights[i][j]) {
        lights[i][j] = 0;
        --switched_off;
      }
    }
  }

  return switched_off;
}

// This function handles the turn ON operation 
int handle_turn_on(unsigned int** idx_mat, int** lights) {
  
  int switched_on = 0;
  unsigned int r0 = idx_mat[0][0];
  unsigned int c0 = idx_mat[0][1];
  unsigned int r1 = idx_mat[1][0];
  unsigned int c1 = idx_mat[1][1];
  
  for (int i = r0; i <= r1; ++i) {
    for (int j = c0; j <= c1; ++j) {
      if (!lights[i][j]) {
        lights[i][j] = 1;
        ++switched_on;
      }
    }
  }

  return switched_on;
}

// Function to handle the soluion of the first part of the riddle
void first_part_solver(FILE* input, int** lights) {
  
  int lights_on = 0;
  inst curr_inst;
  char* temp_name;

  unsigned int** from_to;
  from_to = malloc(2 * sizeof(int*));
  for (int i = 0; i < 2; i++) {
    from_to[i] = malloc(2 * sizeof(int*));
  }

  char* curr_in_line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  
  char** line_tokens;
  line_tokens = malloc(sizeof(char*) * MAX_LINE_TOKENS);
  for (int i = 0; i < MAX_LINE_TOKENS; ++i) {
    line_tokens[i] = malloc(sizeof(char*) * MAX_TOKEN_LENGTH);
  }
 
  while (fgets(curr_in_line, MAX_LINE_LENGTH, input) != NULL) {
    split_instruction_line(curr_in_line, line_tokens);

    if (!strcmp(line_tokens[0], temp_name = "toggle")) {
      curr_inst = TOGGLE;
    } else if (!strcmp(line_tokens[0], temp_name = "turn") && !strcmp(line_tokens[1], temp_name = "off")) {
      curr_inst = TURN_OFF; 
    } else if (!strcmp(line_tokens[0], temp_name = "turn") && !strcmp(line_tokens[1], temp_name = "on")) {
      curr_inst = TURN_ON;  
    } else {
      printf("Unknown instruction read! Program ends...\n");
      return;
    }
    
    if (curr_inst == TOGGLE) {
      get_affected_rnc(line_tokens[1], line_tokens[3], from_to);
    } else {
      get_affected_rnc(line_tokens[2], line_tokens[4], from_to);
    }
 
    switch (curr_inst)
    {
    case TOGGLE:
      //handle toggle
      lights_on += handle_toggle(from_to, lights);
      break;
    case TURN_OFF:
      //handle turn off
      lights_on += handle_turn_off(from_to, lights);
      break;
    case TURN_ON:
      //handle turn on
      lights_on += handle_turn_on(from_to, lights);
      break;
    default:
      printf("Unknown instruction!\n");
      break;
    }    

  }
  printf("Following Santa's instructions, %d lights have been turned on.\n", lights_on);

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