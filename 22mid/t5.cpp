#include <cstdio>
#include <iostream>
using namespace std;

class f {
// 在此处补充你的代码
public:
    int v;
    f(int i):v(i){}
    f(int i,int j):v(i*j){}
    f& operator()(int j){
        v+=j;
        return *this;
    }
    operator int(){
        int tmp=v;
        v=0;
        return tmp;
    }
};

int main() {
  cout << f(4)(5) << endl;
  cout << f(64)(36) << endl;
  cout << f(3)(5)(7) << endl;
  cout << f(3,8) << endl;
  cout << f(15,3) << endl;
  cout << f(7,10) << endl;
}