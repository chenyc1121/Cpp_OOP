#include <stdio.h>
#include <iostream>
using namespace std;
class MyInteger{
public:
  unsigned char C;
  MyInteger(unsigned char c='0'): C(c) {}
// 在此处补充你的代码
    char operator*(MyInteger& other){
        return (C-'0')*(other.C-'0')+'0';
    }
    MyInteger operator+(MyInteger& other){
        return MyInteger(C+other.C-'0');
    }
    operator int(){
        return C-'0';
    }
};

int main() { 
  unsigned char m,n;
  cin >> m >> n;
  MyInteger n1(m), n2(n);
  MyInteger n3;
  n3 = n1*n2;
  MyInteger n4 = n1+n2+n3;
  cout << int(n3) << endl;
  cout << n1+n2+n3 << endl;
  return 0;
}