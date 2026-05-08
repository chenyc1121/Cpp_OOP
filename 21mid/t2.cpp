#include <cstdio>
#include <iostream>
using namespace std;

class f {
// 在此处补充你的代码
public:
    int v=0;
    f(int i){
        v=i;
    }
    f(int i,int j){
        v=i*j;
    }
    f& operator()(int i){
        v=i-v;
        return *this;
    }
    friend ostream& operator<<(ostream& out,const f& m){
        out<<m.v;
        return out;
    }
};

int main() {
  cout << f(3)(5) << endl;
  cout << f(4)(10) << endl;
  cout << f(114)(514) << endl;
  cout << f(9,7) << endl;
  cout << f(2,3) << endl;
  cout << f(2,5) << endl;
}