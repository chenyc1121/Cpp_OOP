#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
    bool status=true;
public:
    MyCin& operator>>(int& n){
        if(!(cin>>n)||n==-1){
            status=false;
            return *this;
        }
        else {
            return *this;
        }
    }
    operator bool(){
        return status;
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}