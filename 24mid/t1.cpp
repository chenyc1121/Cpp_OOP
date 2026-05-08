#include <iostream>
using namespace std;
class A {
	public:
	int val;
	void print() {
		cout << val << endl;
	}
// 在此处补充你的代码
    A(int v=100):val(v){}
    A(const A& other):val(2*other.val){}
};
int main()
{
	int n;
	cin >> n;
	A a(n),b(a),c;
	a.print();  //输出 n 
	b.print();  //输出 2n 
	c.print();  //输出100 
	return 0;
}