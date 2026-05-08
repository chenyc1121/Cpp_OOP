#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
    public:
        int i,j;
        int * a;
    Array2(int i1=0,int j1=0):i(i1),j(j1){ 
        if(i*j)a=new int[i*j];
        else a=NULL;
    }
    Array2(const Array2 & other){
        i=other.i;
        j=other.j;
        a=new int[i*j];
        for(int k=0;k<i*j;k++){
            a[k]=other.a[k];
        }
    }
    ~Array2(){
        if(a)delete [] a;
    }
    Array2 & operator=(const Array2 & other){//赋值运算符参数需要加const，以便用临时对象/const对象赋值
        if(&other==this){
            return *this;
        }
        if(a){
            delete [] a;
        }
        i=other.i;
        j=other.j;
        a=new int[i*j];
        for(int k=0;k<i*j;k++){
            a[k]=other.a[k];
        }
        return *this;
    }
    //[]的重载返回地址，之后的[]不需要重载，正常调用即可
    int * operator[](int row){
        return a+row*j;
    }
    int operator()(int x,int y){
        return a[x*j+y];
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}