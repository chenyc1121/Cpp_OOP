#include <iostream>
using namespace std;
// 在此处补充你的代码
class Base{
    public:
    static int gem; 
    Base(){
        cout<<"Hi Base"<<endl;
    }
    ~Base(){
        cout << "Goodbye Base" << endl;
    }
    static void print_total(){
        cout<<gem<<endl;
    }
    virtual void daily(){
        gem+=60;
    }
};
int Base::gem=0;
class Derived : public Base {
public:
    Derived() {
        cout << "Hi Derived" << endl;
    }
    virtual void daily() {
        gem = gem + 150;
    }
    ~Derived() {
        cout << "Goodbye Derived" << endl;
    }
};

int main() {
    Base    *A = new Base;
    Base    *B = new Derived;
    Derived *C = new Derived;
    Base::print_total();
    A->daily(); 
    Base::print_total();
    B->daily();
    Base::print_total();
    C->daily(); 
    Base::print_total();
    delete A;
    delete B;
    delete C;
}