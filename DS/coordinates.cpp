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
};
