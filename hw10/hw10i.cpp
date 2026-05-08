#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
// 在此处补充你的代码
class Fib{
    int cnt;
    int val;
    int last_val;
    public:
    Fib(int n):cnt(n),val(1),last_val(0){}
    Fib operator++(){
        cnt++;
        int tmp=val;
        val+=last_val;
        last_val=tmp;
        return *this;
    }
    bool operator!=(Fib& other){
        return cnt!=other.cnt;
    }
    int operator*(){
        return val;
    }
};
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;
		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}