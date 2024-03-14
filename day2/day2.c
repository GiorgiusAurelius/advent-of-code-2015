//========== LIBRARIES ==========//
#include <stdio.h>

//========== GLOBAL VARIABLES ==========//
#define SEPARATOR "x"
#define MAX_LINE_LENGTH 15

//========== FUNCTIONS DEFINITIONS ==========//

void ascendant_sorter(unsigned int *array, int array_length) {
  /*
    Function that given an array of uint, sorts its values in ascending order
  */
  int temp = 0;

  for (int i = 0; i <= array_length; i++) {
    for (int j = i + 1; j < array_length; j++) {
      if (array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

unsigned int calculate_box_tot_paper(unsigned int dim[]) {
  /*
    Calculate current box's needed paper 
  */

  unsigned int curr_box_paper;
  unsigned int tot_surface;
  unsigned int smallest_surface;

  tot_surface = 2*dim[0]*dim[1] + 2*dim[0]*dim[2] + 2*dim[1]*dim[2];
  smallest_surface = dim[0]*dim[1];
  
  curr_box_paper = tot_surface + smallest_surface;

  return curr_box_paper;
}

unsigned int calculate_box_tot_ribbon(unsigned int dim[]) {
  /*
    Calculate current box's needed ribbon
  */
  unsigned int curr_box_ribbon;
  unsigned int smallest_perimeter;
  unsigned int volume;

  smallest_perimeter = 2*dim[0]+2*dim[1];
  volume = dim[0]*dim[1]*dim[2];

  curr_box_ribbon = smallest_perimeter + volume;

  return curr_box_ribbon; 
}

void main(){
   
  //========== VARIABLES DECLARATIONS ==========//
  FILE *input;
  char input_path[] = "/home/diego/CProjects/advent-of-code-2015/day2/input.txt";

  char box_dim[MAX_LINE_LENGTH];
  unsigned int lwh[3]; 
  unsigned int tot_paper = 0;
  unsigned int tot_ribbon = 0;
  int lwh_length;

  // Open input file
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when trying to open the input file. The program ends.");
    return;
  }

  // Read input file
  while (fgets(box_dim, MAX_LINE_LENGTH, input) != NULL) {
    sscanf(box_dim, "%dx%dx%d", &lwh[0], &lwh[1], &lwh[2]);
    lwh_length = sizeof(lwh)/sizeof(lwh[0]);
    ascendant_sorter(lwh, lwh_length);
    tot_paper += calculate_box_tot_paper(lwh);
    tot_ribbon += calculate_box_tot_ribbon(lwh);
  }

  printf("Given the box sizes of every present, the elves need: %d" 
  "squared feet of paper and %d feet of ribbon.\n", tot_paper, tot_ribbon);
  fclose(input);

  return;
}