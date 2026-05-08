#include <iostream>
using namespace std;
struct Network {
	int totalConnections;
	void lostAllConnections() {
		cout << "lostAllConnections" << endl;
	}
	Network():totalConnections(0) { }
	void print() {
		cout << totalConnections << endl;
	}
};
class Computer {
// 在此处补充你的代码
    Network* p;
    public:
    Computer(Network& n){
        p=&n;
        n.totalConnections++;
    }
    Computer(Computer& other){
        p=other.p;
        if(p!=nullptr)p->totalConnections++;
    }
    Computer& operator=(Computer& other){
        if(p!=nullptr)p->totalConnections--;
        p=other.p;
        if(p!=nullptr)p->totalConnections++;
        return *this;
    }
    void disConnect(){
        p->totalConnections--;
        if(p->totalConnections==0){
            p->lostAllConnections();
        }
        p=nullptr;
    }
    void connect(Network& n){
        p=&n;
        n.totalConnections++;
    }
    ~Computer(){
        if(p!=nullptr){
            p->totalConnections--;
            if(p->totalConnections==0){
                p->lostAllConnections();
            }
        }
    }
};
int main()
{
	Network net;
	Computer c1(net);
	net.print();
	c1.disConnect();
	Computer c2(c1);
	net.print();
	c1.connect(net);
	c2 = c1;
	net.print();
	Computer * pc3 = new Computer(c2);
	net.print();
	c1.disConnect();
	net.print();
	delete pc3;
	net.print();
	return 0;
}