#include <vector>
#include <cmath>
#include <iostream>

#define UNCLASSIFIED -1
#define CORE_POINT 1
#define BORDER_POINT 2
#define NOISE -2
#define SUCCESS 0
#define FAILURE -3

using namespace std;

struct Point{  
    int x; // first coordinate
    int y; // second coordinate 
    int label; //label
    
    Point(int n_x, int n_y);
};

Point::Point(int n_x, int n_y)
{
    x = n_x;
    y = n_y;
    label = UNCLASSIFIED;
}
