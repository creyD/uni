#include <math.h>
#include <iostream>

using namespace std;

class Coordinate {
  double x;
  double y;
  double z;

public:
  Coordinate(double x_input, double y_input, double z_input){
    x = x_input;
    y = y_input;
    z = z_input;
  }

  bool isOrigin(){
    if (x == 0 && y == 0 && z == 0){
      return true;
    }
    return false;
  }

  void print(){
    cout << "[" << x << ", " << y << ", " << z << "]" << endl;
  }

  void translate(double a, double b, double c){
    x += a;
    y += b;
    z += c;
  }

  double distance(Coordinate point2){
    return sqrt(pow(x - point2.x, 2) + pow(y - point2.y, 2) + pow(z - point2.z, 2));
  }

  bool operator==(const Coordinate point2){
    if (x == point2.x && y == point2.y && z == point2.z){
      return true;
    } else {
      return false;
    }
  }
};

int main(){
  // Testing the data structure
  Coordinate* test1 = new Coordinate(5,1,2);
  Coordinate* test2 = new Coordinate(5,1,2);
  cout << (*test1).distance(*test2) << endl;
  if (*test1 == *test2){
    cout << "Yay" << endl;
  } else {
    cout << "Nope" << endl;
  }
  delete test1;
  delete test2;
  return 0;
}
