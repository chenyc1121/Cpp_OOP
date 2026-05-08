#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename F1,typename F2,typename T>
class combine{
    F1 f;
    F2 g;
    public:
    combine(F1 f1,F2 f2):f(f1),g(f2){}
    T operator()(T v){
        return f(f(v)+g(v));
    }
};
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}