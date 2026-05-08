#include <iostream> 
using namespace std;
class MyInt 
{ 
	int nVal; 
	public: 
	MyInt( int n) { nVal = n ;}
// 在此处补充你的代码
    MyInt & operator-(int k){
        nVal-=k;
        return *this;
    }
	//类型转换运算符的重载——>不需要写出返回值（类型转换本身已经体现了返回值）；
	//					   不需要参数（若重载为成员函数）
    operator int() {
        return nVal;
    }
}; 
int Inc(int n) {
	return n + 1;
}
int main () { 
	int n;
	while(cin >>n) {
		MyInt objInt(n); 
		objInt-2-1-3; 
		cout << Inc(objInt);
		cout <<","; 
		objInt-2-1; 
		cout << Inc(objInt) << endl;
	}
	return 0;
}