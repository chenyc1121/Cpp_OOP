#include <iostream>
#include <vector>
using namespace std;
// 在此处补充你的代码
template<typename T1, typename T2 = greater<int> >
class getWanted {
    T1 st, ed;
    // 关键：定义一个底层通用的函数指针
    bool (*comp)(int, int);

    // 辅助模板函数：将各种比较器（less, myComp等）转为统一的函数指针
    template<typename T3>
    static bool wrapper(int a, int b) {
        return T3()(a, b);
    }

public:
    // 两个参数的情况：使用类模板默认的 T2
    getWanted(T1 s, T1 e) : st(s), ed(e), comp(wrapper<T2>) {}

    // 三个参数的情况：捕捉实际的 T3 类型
    template<typename T3>
    getWanted(T1 s, T1 e, T3 f) : st(s), ed(e), comp(wrapper<T3>) {}

    friend ostream& operator<<(ostream& out, const getWanted& w) {
        T1 best = w.st;
        for (T1 it = w.st; it != w.ed; ++it) {
            if (w.comp(*best, *it)) best = it;
        }
        out << *best;
        return out;
    }
};
struct myComp {
	bool operator ()(int a,int b) {
		return a % 10 < b % 10;
	}
};
int main()
{
	int n;
	cin >> n;
	vector<int> a,b,c;
	for(int i=0;i<n;++i) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	int cmd;
	while( cin >> cmd ) {
		switch(cmd) {
			case 0:
				cout << getWanted<vector<int>::iterator,less<int>>(a.begin(),a.end()) << endl;
				break;
			case 1:
				cout << getWanted<vector<int>::iterator>(a.begin(),a.end(), less<int>()) << endl;	
				break;
			case 2:
				cout << getWanted<vector<int>::iterator>(a.begin(),a.end(),myComp()) << endl;
				break;
			case 3:
				cout << getWanted<vector<int>::iterator>(a.begin(),a.end()) << endl; 
				break;
		}
	}
	return 0;
}