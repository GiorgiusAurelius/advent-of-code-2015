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

  int santa_x = starting_edge / 2;
  int santa_y = starting_edge / 2;
  int robo_santa_x = starting_edge / 2;
  int robo_santa_y = starting_edge / 2;

  houses[santa_y][santa_x]++;

  int new_x, new_y;

  int houses_visited_once = 1;
  int direction_count = 0;

  // Open input file                                                       
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when trying to open the input file. The program ends.\n");
    return;
  }

  // Read the instructions  
  while ((direction_token = fgetc(input)) != EOF) {
    direction_count++;
    switch (direction_token) {

      case NORTH:
        if (direction_count % 2 == 1) {
          santa_y--;
          houses[santa_y][santa_x]++;
          if (houses[santa_y][santa_x] == 1) {
            houses_visited_once++;
          }
        } else {
          robo_santa_y--;
          houses[robo_santa_y][robo_santa_x]++;
          if (houses[robo_santa_y][robo_santa_x] == 1) {
            houses_visited_once++;
          }
        }
        break;

      case SOUTH:
        if (direction_count % 2 == 1) {
          santa_y++;
          houses[santa_y][santa_x]++;
          if (houses[santa_y][santa_x] == 1) {
            houses_visited_once++;
          }
        } else {
          robo_santa_y++;
          houses[robo_santa_y][robo_santa_x]++;
          if (houses[robo_santa_y][robo_santa_x] == 1) {
            houses_visited_once++;
          }
        }
        break;

      case EAST:
        if (direction_count % 2 == 1) {
          santa_x++;
          houses[santa_y][santa_x]++;
          if (houses[santa_y][santa_x] == 1) {
            houses_visited_once++;
          }
        } else {
          robo_santa_x++;
          houses[robo_santa_y][robo_santa_x]++;
          if (houses[robo_santa_y][robo_santa_x] == 1) {
            houses_visited_once++;
          }
        }
        break;

      case WEST:
        if (direction_count % 2 == 1) {
          santa_x--;
          houses[santa_y][santa_x]++;
          if (houses[santa_y][santa_x] == 1) {
            houses_visited_once++;
          }
        } else {
          robo_santa_x--;
          houses[robo_santa_y][robo_santa_x]++;
          if (houses[robo_santa_y][robo_santa_x] == 1) {
            houses_visited_once++;
          }
        }
        break;

      default:
        printf("The read character isn't a valid direction. Got: %c.\n", direction_token);
        break;
    }
  }

  printf("Santa and robosanta have visited %d houses at least once.\n", houses_visited_once);

  free(houses);
  fclose(input);
  return;
}