#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename T1,typename T2>
class f{
    T1 a{};
    T2 b{};
    public:
    f(T1 x){
        a=x;
    }
    auto operator()(T2 y){
        return y+a;
    }
};
int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}