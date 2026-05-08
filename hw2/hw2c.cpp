#include <iostream>
using namespace std;
class Sample {
public:
	int v;
// 在此处补充你的代码
	Sample(const Sample & other):v(other.v+2){}
	Sample(int val=0):v(val){}
};
void PrintAndDouble(Sample o)//值传递——>调用复制构造函数
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}