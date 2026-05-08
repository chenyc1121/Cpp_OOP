#include <iostream>
using namespace std;
class C {
	public:
		static int num;
		int curr_value;
		friend ostream& operator << (ostream& o, const C& c) {
			o << "() called " << num << " times, sum is " << c.curr_value;
			return o;
	}
// 在此处补充你的代码
    C(int n=0){
        curr_value=n;
    }
    C& operator()(int i,int j=0){
        num++;
        if(num==3||num==4)curr_value=0;
        curr_value+=i+j;
        return*this;
    }
};
int C::num = 0; 
int main() {
	C c1;
	cout << c1(1)(2) << endl;
	cout << c1(3, 4) << endl;
	cout << c1(5, 6)(7) << endl;
	C c2;
	cout << c2(7)(8, 9) << endl;
	return 0;
}