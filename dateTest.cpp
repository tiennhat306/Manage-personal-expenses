#include <iostream>
#include "DateTime.cpp"

using namespace std;

int main(){
    DateTime a(1,1,1990);
    DateTime b(1,1,1990);
    
    cout << a + 30;
    return 0;
}