#include <iostream>

// Include time header for random number generation
#include <time.h>

// Include chrono for measuring the time
#include <chrono>

using namespace std;

bool verbose = false;

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
  for (int i = 0; i < length; i++){
    int var = rand() % length;
    while (true){
      if (inList(list, i + 1, var)){
        var = rand() % length;
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
  for (int i = 0; i < length; i++){
    list[i] = rand() % length;
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

int main(int argc, char* argv[]){
  if (argc > 2){
    // Get the second command line argument
    int list_length = atoi(argv[2]);

    // If the list length is invalid --> end the programm
    if (list_length != 0){
      // Reserve memory for the list
      int *the_list = new int[list_length];

      // Check if a population mode is provided, if not use default generation
      int gen_mode = 0;
      if (argc > 3){
        gen_mode = atoi(argv[3]);
      }

      // Populate the list with values according to the population mode
      switch (gen_mode){
        case 1:
          genList(the_list, list_length);
          break;
        case 2:
          cout << "Generating sorted list." << endl;
          genListGood(the_list, list_length);
          break;
        case 3:
          cout << "Generating inversly sorted list." << endl;
          genListBad(the_list, list_length);
          break;
        case 4:
          cout << "Generating list with duplicate values." << endl;
          genListDup(the_list, list_length);
          break;
        default:
          genList(the_list, list_length);
          break;
      }

      // Print the initial state
      if (verbose){
        cout << "Initial State:" << endl;
        printList(the_list, list_length);
      }

      cout << "Starting sorting..." << endl;

      // Sort the list with the selected algoithm
      auto start = chrono::high_resolution_clock::now();
      switch (atoi(argv[1])) {
        case 1:
          cout << "Bubble Sort selected." << endl;
          sort_bubble(the_list, list_length);
          break;
        case 2:
          cout << "Selection Sort selected." << endl;
          sort_selection(the_list, list_length);
          break;
        default:
          cout << "Invalid algorithm selection (first command line parameter)." << endl;
          break;
      }

      // Clock time
      auto finish = chrono::high_resolution_clock::now();

      cout << "Finished sorting..." << endl;

      // Calculate time
      auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
      if (duration > 1000000){
        cout << "Time: " << duration / 1000000 << " s" << endl;
      } else if (duration > 1000){
        cout << "Time: " << duration / 1000 << " ms" << endl;
      } else {
        cout << "Time: " << duration << " microseconds" << endl;
      }

      // Print the final state of the list
      if (verbose){
        cout << "Final State:" << endl;
        printList(the_list, list_length);
      }
    }
    else {
      cout << "List size invalid (second command line parameter)." << endl;
    }
  } else {
    cout << "Not enough command line parameters provided." << endl;
  }
  return 0;
}
