#include <iostream>
using namespace std;

class IntStack {
  struct Knoten {
    int wert;
    Knoten* previous;
  };

  Knoten* kopf;

public:
  IntStack(int value){
    Knoten* first = new Knoten();
    first->wert = value;
    first->previous = NULL;
    kopf = first;
  }

  ~IntStack(){
    while(true){
      if (!(kopf->previous == NULL)){
        pop();
      }
      delete kopf;
    }
  }

  int getHead(){
    return kopf->wert;
  }

  bool isEmpty(){
    if (kopf->previous == NULL){
      return true;
    }
    return false;
  }

  void push(int element){
    Knoten* new_knoten = new Knoten();
    new_knoten->wert = element;
    new_knoten->previous = kopf;
    kopf = new_knoten;
  }

  void pop(){
    if (!(kopf->previous == NULL)){
      kopf = kopf->previous;
    } else {
      cout << "Löschung nicht möglich. Liste wäre leer." << endl;
    }
  }
};

int main(){
  // TESTING
  IntStack* test = new IntStack(5);
  cout << test->getHead() << endl;
  test->push(8);
  cout << test->getHead() << endl;
  test->pop();
  cout << test->getHead() << endl;
  test->pop();
  cout << test->getHead() << endl;
  delete test;
  return 1;
}
