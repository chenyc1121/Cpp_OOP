#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(T* begin,T* end){
// 在此处补充你的代码
    T ret{};//用花括号初始化
    for(T* p=begin;p<end;p++){
        ret+=*p;
    }
    return ret;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}