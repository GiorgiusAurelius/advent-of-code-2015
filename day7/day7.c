#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define HASH_TABLE_SIZE 676 // 26 * 26 
#define MAX_GATE_LENGTH 15
#define ASCII_a 97
#define ASSIGNER "->"

const char assigner[3] = "->";

typedef enum {false, true} bool;

typedef struct {
  char* wire_name;
  unsigned short signal;
  bool gate_valued;
  char* gate;
} wire_n_gate;

// ========================== //
//    HASH TABLE FUNCTIONS    //
// ========================== //

wire_n_gate * hash_table[HASH_TABLE_SIZE];

// The idea of this hash function is to match each wire_name (from 'a' to 'zz') to an index in the array
unsigned int hash_function(char* key) {
  unsigned int index = 0;
  unsigned int key_length = strlen(key);
  printf("key: %s, key length: %d\n", key, key_length);

  if (key_length == 2) {
    index += ((unsigned int)key[0] - ASCII_a + 1) * 26;
    index += ((unsigned int)key[1] - ASCII_a);
    index = index % HASH_TABLE_SIZE;
  } else if (key_length == 1) {
    // index: 'a' = 0 -> ... -> 'z' = 25
    index = ((unsigned int)key[0] - ASCII_a);
    index = index % HASH_TABLE_SIZE;
  }

  return index;  
}

void init_hash_table() {
  for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
    hash_table[i] = NULL;
  }
  //table is empty
}

bool hash_insert(wire_n_gate w) {
  if (&w == NULL) return false;

  wire_n_gate* temp = malloc(sizeof(wire_n_gate));
  if (temp == NULL) {
    return false; //Memory allocation failed
  }

  temp->wire_name = malloc(strlen(w.wire_name) * sizeof(char));
  strcpy(temp->wire_name, w.wire_name);
  temp->gate = malloc(strlen(w.gate) * sizeof(char));
  strcpy(temp->gate, w.gate);

  unsigned int idx = hash_function(w.wire_name);
  printf("idx: %d\n", idx);
  printf("Wire name: %s, gate: %s\n", w.wire_name, w.gate);
  if (hash_table[idx] == NULL) {
    hash_table[idx] = temp;
    return true;
  }
  return false;
}

void table_printer() {
  printf("START\n\n");
  for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
    if (hash_table[i] != NULL) {
      printf("\t%d\twire_name: %s, gate: %s\n", i, hash_table[i]->wire_name, hash_table[i]->gate);
    }
  }
  printf("\nEND\n");
}

void free_hash_table() {
  for (int i = 0; i< HASH_TABLE_SIZE; ++i) {
    if (hash_table[i] != NULL) {
      free(hash_table[i]);
    }
  }
}

// ========================== //
//        INPUT READER        //
// ========================== //

void parser(char* line) {
  //printf("Parser in...\n");
  wire_n_gate temp;
  
  // Retrieve gate
  char* token = strtok(line, assigner);
  temp.gate = malloc(strlen(token) * sizeof(char));
  strncpy(temp.gate, token, strlen(token));
  temp.gate[strlen(token)-1] = '\0';
  
  // Retrieve wire name
  token = strtok(NULL, assigner);
  temp.wire_name = malloc(strlen(token) * sizeof(char));
  //Remove space
  memmove(token, token+1, strlen(token));
  
  strncpy(temp.wire_name, token, strlen(token));
  temp.wire_name[strlen(token)-1] = '\0';
  
  if (!hash_insert(temp)) {
    printf("Couldn't insert element in the table, a collision has been produced!\n");
  }

  //printf("Wire name: %s, gate: %s\n", hash_table[hash_function(temp.wire_name)]->wire_name, hash_table[hash_function(temp.wire_name)]->gate);
  //printf("Parser out...\n");
}

void solve_part1(FILE* input) {
  //printf("Solver1 in..\n");
  char* curr_line = malloc(MAX_LINE_LENGTH * sizeof(char));

  while (fgets(curr_line, MAX_LINE_LENGTH, input) != NULL) {
    printf("Before parser...\n");
    parser(curr_line);
  }
  table_printer();
  free(curr_line);
}

void solve_part2(FILE* input) {

}

int main() {
  
  FILE* input;
  char* input_path = "/home/diego/CProjects/advent-of-code-2015/day7/input_test.txt";
  bool first_riddle_part = true;

  if ((input = fopen(input_path, "r")) == NULL) {
    printf("Problem in opening the input file. The program ends...\n");
    return EXIT_FAILURE;
  }

  init_hash_table();

  //printf("Enter solvers...\n");
  if (first_riddle_part) {
    solve_part1(input);
  } else {
    solve_part2(input);    
  }

//  printf("Hash_table el23 = %s, %s", hash_table[23]->wire_name, hash_table[23]->gate);
  free_hash_table();
  fclose(input);
  return EXIT_SUCCESS;
}