#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

// Generate List
int list_length = 10;
int *the_list = new int[list_length];

// Modes (1 = Bubble Sort, 2 = Insertion Sort)
int mode = 1;

// HELPER FUNCTIONS
// Swaps two values in the list
void swap(int& a, int& b){
  int c = a;
  a = b;
  b = c;
  return;
}

// Returns true if the list is already sorted
bool isSorted(int* list, int length){
  for (int i = 0; i < length - 1; i++){
    if (list[i] > list[i+1]){
      return false;
    }
  }
  return true;
}

// Returns true if a value is in the list
bool inList(int* list, int length, int value){
    for (int i = 0; i < length - 1; i++){
      if (list[i] == value){
        return true;
      }
    }
    return false;
}

// Returns the index of the smallest number in the list
int getSmallest(int* list, int length){
  int smallest = list[0];
  int smallest_index = 0;
  for (int i = 0; i < length - 1; i++){
    if (list[i] < smallest){
      smallest = list[i];
      smallest_index = i;
    }
  }
  return smallest_index;
}

// Prints the list in the console
void printList(int* list, int length){
  for (int i = 0; i < length; i++){
    if (i == 0){
      cout << "[" << list[i] << ", ";
    }
    else if (i == length - 1){
      cout << list[i] << "]" << endl;
    }
    else {
      cout << list[i] << ", ";
    }
  }
  return;
}

// Populates empty list with unique values
void genList(int* list, int length){
  srand(time(NULL));
  for (int i = 0; i < list_length; i++){
    int var = rand() % list_length;
    while (true){
      if (inList(list, i + 1, var)){
        var = rand() % list_length;
      } else {
        break;
      }
    }
    list[i] = var;
  }
  return;
}

// Populates empty list with values (can contain duplicates)
void genListDup(int* list, int length){
  srand(time(NULL));
  for (int i = 0; i < list_length; i++){
    list[i] = rand() % list_length;
  }
  return;
}

// Best case: array already is sorted
void genListGood(int* list, int length){
  for (int i = 0; i < length; i++){
    list[i] = i;
  }
  return;
}

// Worst case: array is inverse
void genListBad(int* list, int length){
  for (int i = 0; i < length; i++){
    list[i] = (length - 1) - i;
  }
  return;
}

// ALGORITHMS
// Bubble sort algoithm
void sort_bubble(int* list, int length){
  while (true){
    if (isSorted(list, length)){
      break;
    } else {
      for (int i = 0; i < length - 1; i++){
        if (list[i] > list[i + 1]){
          swap(list[i], list[i + 1]);
        }
      }
    }
  }
  return;
}

// Selection sort algorithm
void sort_selection(int* list, int length){
  for (int i = 0; i < length - 1; i++){
    int min = i;
    for (int j = i + 1; j < length; j++){
      if (list[j] < list[min]){
        min = j;
      }
    }
    swap(list[i], list[min]);
  }
  return;
}

int main(){
  // Generate a unique list list
  genList(the_list, list_length);

  // Print the initial state
  cout << "Initial State:" << endl;
  printList(the_list, list_length);

  // Sort the list with the selected algoithm
  if (mode == 1){
    sort_bubble(the_list, list_length);
  } else if (mode == 2){
    sort_selection(the_list, list_length);
  }

  // Print the final state of the list
  cout << "Final State:" << endl;
  printList(the_list, list_length);
  return 0;
}
