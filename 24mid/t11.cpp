#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
template<typename T1, typename T2 = less<T1>>
class Comparator {
    T2 cmp;

    bool compare(const T1& x, const T1& y, less<T1>) {
        return x < y;
    }

    template<typename F>
    bool compare(const T1& x, const T1& y, F) {
        return F()(x) < F()(y);
    }

public:
    bool operator()(const T1& x, const T1& y) {
        return compare(x, y, cmp);
    }
};
struct len {
	int operator() (string s){
		return s.length();
	}
};
int main() 
{
	int a[8] {4,2,1,3,5,6,8,7};
	sort(a,a+8,Comparator<int>());
	for( int x : a)
		cout << x << " ";
	cout << endl;
	int n;
	vector<string> v;
	cin >> n;
	for(int i=0;i< n; ++i) {
		string s;
		cin >> s;
		v.push_back(s);
	}			
	sort(v.begin(),v.end(),Comparator<string>());
	for( string x : v)
		cout << x << " ";
	cout << endl;
	
	sort(v.begin(),v.end(),Comparator<string,len>());
	for( string x : v)
		cout << x << " ";
	 
	return 0;
}