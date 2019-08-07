#include <math.h>
#include <iostream>

using namespace std;

class Coordinate {
  double x;
  double y;
  double z;

public:
  Coordinate(){
    x = y = z = 0;
  }

  Coordinate(double x_input, double y_input, double z_input){
    x = x_input;
    y = y_input;
    z = z_input;
  }

  double getX(){
    return x;
  }

  double getY(){
    return y;
  }

  double getZ(){
    return z;
  }

  void setX(double a){
    x = a;
  }

  void setY(double a){
    y = a;
  }

  void setZ(double a){
    z = a;
  }

  void setX(int a){
    x = (double) a;
  }

  void setY(int a){
    y = (double) a;
  }

  void setZ(int a){
    z = (double) a;
  }

  bool isOrigin(){
    if (x == 0 && y == 0 && z == 0){
      return true;
    } else {
      return false;
    }
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

  bool operator==(Coordinate point2){
    if (x == point2.x && y == point2.y && z == point2.z){
      return true;
    } else {
      return false;
    }
  }

   void operator=(Coordinate point2){
    x = point2.x;
    y = point2.y;
    z = point2.z;
    return;
  }

  void operator+=(Coordinate point2){
    x += point2.x;
    y += point2.y;
    z += point2.z;
    return;
  }

  Coordinate* operator+(Coordinate point2){
    Coordinate* result = new Coordinate(x + point2.x, y + point2.y, z + point2.z);
    return result;
  }
};

int main(){
  // Testing the data structure
  Coordinate* test1 = new Coordinate();
  (*test1).print();
  Coordinate* test2 = new Coordinate(5,1,2);
  (*test1) += (*test2);
  Coordinate* test3 = (*test1) + (*test2);
  (*test3).print();
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
