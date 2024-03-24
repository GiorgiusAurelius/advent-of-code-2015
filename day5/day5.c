#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_LINE_TOKEN '!'

typedef enum {false, true} bool;

bool is_vowel(char letter) {
  bool vowel = false;

  if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
    vowel = true;
  }

  return vowel;
}

bool check_wrong_strings(char prev_letter, char curr_letter){
  bool is_wrong_string = false;

  //printf("Prev_token = %c \t Curr_token = %c\n", prev_letter, curr_letter);
  if (prev_letter == 'a' && curr_letter == 'b') {
    is_wrong_string = true;
  } else if (prev_letter == 'c' && curr_letter == 'd') {
    is_wrong_string = true;
  } else if (prev_letter == 'p' && curr_letter == 'q') {
    is_wrong_string = true; 
  } else if (prev_letter == 'x' && curr_letter == 'y') {
    is_wrong_string = true;
  }

  return is_wrong_string;
}

int main() {

  FILE* input;
  char* input_path = "/home/diego/CProjects/advent-of-code-2015/day5/input.txt";  

  int num_vowels = 0;
  int nice_strings = 0;
  bool vowels_ok = false;
  bool double_letter_ok = false;
  bool no_wrong_strings = true;

  char prev_token = INIT_LINE_TOKEN;
  char curr_token = INIT_LINE_TOKEN;
  
  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Error when opening the input file!\n The program ends.\n");
    return EXIT_FAILURE;
  }

  while ((curr_token = fgetc(input)) != EOF) {
    if (curr_token != '\n') {
      if (is_vowel(curr_token)) {
        ++num_vowels;
      }
      if (num_vowels >= 3 && !vowels_ok) {
        vowels_ok = true;
      }
      if (curr_token == prev_token && !double_letter_ok) {
        double_letter_ok = true;
      }
      if (check_wrong_strings(prev_token, curr_token)) {
        no_wrong_strings = false;
      } 
    } else {
      //printf("Num vowels = %d\n", num_vowels);
      //printf("vowels_ok: %d, double_letter_ok: %d, no_wrong_strings: %d\n", vowels_ok, double_letter_ok, no_wrong_strings); 
      if (vowels_ok && double_letter_ok && no_wrong_strings) {
        ++nice_strings;
      }
      prev_token = INIT_LINE_TOKEN;
      curr_token = INIT_LINE_TOKEN;
      num_vowels = 0;
      vowels_ok = false;
      double_letter_ok = false;
      no_wrong_strings = true;
    }
    prev_token = curr_token;
  }

  printf("Among the strings Santa read %d are correct ones!\n", nice_strings);
  // Close input file
  fclose(input);

  return EXIT_SUCCESS;
}