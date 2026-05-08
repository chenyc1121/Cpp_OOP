#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
// 在此处补充你的代码
template<typename T=int>
class MyAccumulate{
    public:
    MyAccumulate(){}
    T operator()(T* st,int n, T(*f)(T)){
        T ret{};
        for(T* i=st;i<st+n;i++){
            ret+=f(*i);
        }
        return ret;
    }
    template<typename T1>
    friend ostream& operator<<(ostream& out,const MyAccumulate& m){
        T1 ret{};
        for(T1* i=m.st;i<m.st+m.n;i++){
            ret+=m.f(*i);
        }
        out<<ret;
        return out;
    }
};
template<class T>
class Myaccumulate {
    T res;
public:
    Myaccumulate(T* st, int n, T (*f)(T)) {
        res = T();
        for (int i = 0; i < n; ++i) {
            res += f(st[i]);
        }
    }
    friend ostream& operator<<(ostream& os, const Myaccumulate& m) {
        os << m.res;
        return os;
    }
};

int sqr(int n) {
    return n * n;
}
string rev(string s){
    return string(s.rbegin(),s.rend()); ;
}
int main() {
    int a[100];
    string b[100];
    int n;
    cin >> n;
    for(int i = 0;i < n; ++i)
      cin >> a[i];
    for(int i = 0;i < n; ++i)
      cin >> b[i];
    cout << Myaccumulate(a, n, sqr) << endl;
    cout << Myaccumulate(b, n, rev) << endl;
    cout << MyAccumulate<int>()(a, n-1, sqr) << endl;
    cout << MyAccumulate<string>()(b+1, n-1, rev) << endl;
    return 0;
}