#include <iostream>
using namespace std;
class A{
protected:
    int x;
public:
    A(int a=1){
        cout << "construct A" << endl;
        x = a;
    }
    virtual void show(){
        cout << "A:"  << x << endl;
    }
};
// 在此处补充你的代码
class B:public A{
    public:
    B(int a=2):A(a){    }
    void show(){
        A::show();
        cout << "B:"  << x << endl;
    }
};
class C:public A{
    public:
    C(int a=3):A(a){    }
    void show(){
        A::show();
        cout << "C:"  << x << endl;
    }
};
int main(){
    A a, *pa;
    B b;
    C c;
    pa = &a; pa->show();
    pa = &b; pa->show();
    pa = &c; pa->show();
}