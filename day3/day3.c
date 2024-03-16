//========== LIBRARIES ==========//
#include <stdio.h>

//========== GLOBAL VARIABLES ==========//
#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

typedef struct house {
  int presents;
  struct house * north;
  struct house * south;
  struct house * east;
  struct house * west;
} house_t;


//========== FUNCTIONS DEFINITIONS ==========//
house_t* create_house() {
  /*
    Function that generates a new node.
  */
  house_t* new_house = (house_t*) malloc(sizeof(house_t));

  //Check that the meory has been allocated properly
  if (new_house == NULL) {
    printf("The memory couldn't be allocated correctly!\n");
    return NULL;
  }

  new_house->presents = 1;

  new_house->north = NULL;
  new_house->south = NULL;
  new_house->east = NULL;
  new_house->west = NULL;

  return new_house;
}

//========== MAIN BODY ==========//
void main() {

  //========== VARIABLES DECLARATIONS ==========//
  FILE *input;
  char input_path[] = "/home/diego/CProjects/advent-of-code-2015/day3/input.txt";  
  char direction_token;

  house_t *starting_house = create_house();
  if (starting_house != NULL) {
    printf("Starting house created succesfully!\n");
  }
  //TODO : Remember you need to free the allocated memory!!!
  house_t *curr_house = starting_house;

  // Open input file                                                       
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when trying to open the input file. The program ends.\n");
    return;
  }

  // Read the instructions and create the tree of houses
  while ((direction_token = fgetc(input)) != EOF) {
    switch (direction_token) {
      case NORTH:

        if (curr_house->north == NULL) {
          // Create a new house and link it to the current one
          curr_house->north = create_house();
          curr_house->north->south = curr_house;
        } else {
          curr_house->north->presents ++;
        }
        // Move Santa to the new house
        curr_house = curr_house->north;
        break;

      case SOUTH:

        if (curr_house->south == NULL) {
          // Create a new house and link it to the current one
          curr_house->south = create_house();
          curr_house->south->north = curr_house;
        } else {
          curr_house->south->presents ++;
        }
        // Move Santa to the new house
        curr_house = curr_house->south;
        break;

      case EAST:

        if (curr_house->east == NULL) {
          // Create a new house and link it to the current one
          curr_house->east = create_house();
          curr_house->east->west = curr_house;
        } else {
          curr_house->east->presents ++;
        }
        // Move Santa to the new house
        curr_house = curr_house->east;
        break;

      case WEST:

        if (curr_house->west == NULL) {
          // Create a new house and link it to the current one
          curr_house->west = create_house();
          curr_house->west->east = curr_house;
        } else {
          curr_house->west->presents ++;
        }
        // Move Santa to the new house
        curr_house = curr_house->west;
        break;

      default:
        printf("The read character isn't a valid direction. Got: %c.\n", direction_token);
        break;
    }
  }
  
  return;
}