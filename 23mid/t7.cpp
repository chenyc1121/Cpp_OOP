#include <iostream>
#include <string>
using namespace std;

class MyCout{
    public:
    int sum;
    MyCout():sum(0){}
    MyCout& operator<<(int n){
        sum+=n;
        return *this;
    }
    ~MyCout(){
        cout<<sum;
    }
};
// 在此处补充你的代码
int main() {
    MyCout mycout;
    int n;
    while (cin >> n)
        mycout << n; 
    return 0;
}