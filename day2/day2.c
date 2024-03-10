//========== LIBRARIES ==========//
#include <stdio.h>

//========== GLOBAL VARIABLES ==========//
#define SEPARATOR "x"
#define MAX_LINE_LENGTH 15

//========== FUNCTIONS DEFINITIONS ==========//

unsigned int calculate_box_tot_area(unsigned int l, unsigned int w, unsigned int h) {

  unsigned int curr_box_area;
  unsigned int dim[3] = {l, w, h};

  // Sort array to find the smallest face in terms of area
  int temp = 0;
  int array_length = sizeof(dim)/sizeof(dim[0]);
  for (int i = 0; i <= array_length; i++) {
    for (int j = i + 1; j < array_length; j++) {
      if (dim[i] > dim[j]) {
        temp = dim[i];
        dim[i] = dim[j];
        dim[j] = temp;
      }
    }
  }

  // Calulate the area of the box and add the slack
  curr_box_area = 2*l*w + 2*l*h + 2*w*h + dim[0]*dim[1];
  
  return curr_box_area;
}

void main(){
   
  //========== VARIABLES DECLARATIONS ==========//
  FILE *input;
  char input_path[] = "/home/diego/CProjects/advent-of-code-2015/day2/input.txt";

  char box_dim[MAX_LINE_LENGTH];
  unsigned int length = 0;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int tot_paper = 0;

  // Open input file
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when trying to open the input file. The program ends.");
    return;
  }

  // Read input file
  while (fgets(box_dim, MAX_LINE_LENGTH, input) != NULL) {
    sscanf(box_dim, "%dx%dx%d", &length, &width, &height);
    tot_paper += calculate_box_tot_area(length, width, height);
  }

  printf("Given the box sizes of every present, the elves need: %d squared feet of paper.\n", tot_paper);
  fclose(input);

  return;
}