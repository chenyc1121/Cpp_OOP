#include <iostream>
using namespace std;
class Sample {
public:
	int my_value;
    static int sum;
    Sample(int v=0):my_value(v){
        sum+=v;
    }
    Sample(const Sample& other):my_value(other.my_value){
        sum+=my_value;
    }
    ~Sample(){
        sum-=my_value;
    }
};
int Sample::sum=0;
// 在此处补充你的代码
int main()
{
	Sample a(5);
	cout<<Sample::sum<<endl;
	Sample b = a;
	cout << Sample::sum << endl;
	Sample c;
	cout << Sample::sum << endl;
	Sample * d = new Sample(20);
	cout << Sample::sum<<endl;
	delete d;
	cout << Sample::sum<<endl;
	return 0;
}