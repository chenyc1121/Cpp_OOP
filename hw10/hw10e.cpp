#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat{
	int h,w;
public:
	Mat(int height,int width):h(height),w(width),sum(0),mycnt(count){
        p=new int[h*w];
        count++;
    }
    int* p;
    int sum;
    int mycnt;
    static int count;
    bool operator<(Mat& other){
        if(h*w==other.h*other.w)return mycnt>other.mycnt;
        else return h*w<other.h*other.w;
    }
    friend istream& operator>>(istream& in,Mat& m){
        for(int i=0;i<m.h;i++){
            for(int j=0;j<m.w;j++){
                in>>m.p[i*m.w+j];
                m.sum+=m.p[i*m.w+j];
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out,Mat& m){
        for(int i=0;i<m.h;i++){
            for(int j=0;j<m.w;j++){
                out<<m.p[i*m.w+j]<<" ";
            }
            out<<endl;
        }
        return out;
    }
};
bool comparator_1(Mat& x,Mat& y){
    if(x.sum==y.sum)return x.mycnt>y.mycnt;
    else return x.sum<y.sum;
}
class comparator_2{
    public:
    bool operator()(Mat& x,Mat& y){
        return x.mycnt<y.mycnt;
    }
};
int Mat::count = 0;
// 在此处补充你的代码
int main()
{
	vector<Mat> m;
	m.push_back(Mat(2,2));
	m.push_back(Mat(3,4));
	m.push_back(Mat(2,2));
	cin >> m[0] >> m[1] >> m[2];
	sort(m.begin(),m.end());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_1);
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_2());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	return 0;
}