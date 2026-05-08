#include <iostream>
#include <string>
using namespace std;
// 在此处补充你的代码
template<typename T,typename F>
void MyForeach(T* begin,T* end,F func){
    for(T* p=begin;p<end;p++){
        func(*p);
    }
}
void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string aarray[100];
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> aarray[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(aarray,aarray+m,Print);		 
		cout << endl;
		MyForeach(a,a+n,Inc);		 
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}