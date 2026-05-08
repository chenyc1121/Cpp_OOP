#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T, class Compare = less<T>>
class MaxFinder {
    T* first;
    T* last;
public:
    MaxFinder(T* f, T* l) : first(f), last(l) {}

    T* getMax() {
        T* best = first;
        Compare cmp;
        for (T* p = first + 1; p != last; ++p) {
            if (cmp(*best, *p)) best = p;
        }
        return best;
    }

    template <class C>
    T* getMax(C cmp) {
        T* best = first;
        for (T* p = first + 1; p != last; ++p) {
            if (cmp(*best, *p)) best = p;
        }
        return best;
    }
};
bool cmp(int a,int b)
{
	return a % 10 < b % 10;
}
struct op {
	bool operator()(int a,int b) {
		return a % 7 < b % 7;
	}
};
int main()
{
	int a[8];
	for(int i=0;i < 8; ++i)
		cin >> a[i];
	MaxFinder<int> mf1(a,a+8);
	int cmd;
	cin >> cmd;
	switch(cmd) {
		case 0:
			cout << * mf1.getMax() << endl;
			break;
		case 10:
			cout << * mf1.getMax(cmp) << endl;
			break;
		case 7:
			cout << * mf1.getMax(op()) << endl;		 
	}
	MaxFinder<int,op> mf2(a,a+8);
	cout << * mf2.getMax() << endl;		 
	return 0;
}