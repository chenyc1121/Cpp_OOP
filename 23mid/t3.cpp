#include <iostream>
using namespace std;

class A {
public:
// 在此处补充你的代码
static int total;
A(int i=0,int j=0){
    total++;
}
A(const A& other){
    total++;
}
~A(){
    total--;
}
};

int A::total = 0;

int main() {
    A array1[4];
    cout << A::total << "\n";
    A array2[4] = {1, A(1,1)};
    cout << A::total << "\n";
    A a(array1[0]);
    cout << A::total << "\n";
    A * p = new A();
    cout << A::total << "\n";
    delete p;
    cout << A::total << "\n";
    return 0;
}