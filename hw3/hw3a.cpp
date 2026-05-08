#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if(s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;
	}
	~MyString() { if(p) delete [] p; }
// 在此处补充你的代码
    //构造函数不需要判自赋值、已有指针
    MyString(const MyString & other){
        if(other.p){
            p=new char[strlen(other.p)+1];
            strcpy(p,other.p);
        }
        else {
            p=NULL;
        }
    }

    //需要先判断是否已有指针
    MyString & Copy(const char* other){
        if(p){
            delete [] p;
        }
        if(other){
            p=new char[strlen(other)+1];
            strcpy(p,other);
        }
        else {
            p=NULL;
        }
        return *this;//注意返回
    }

    //需要判断自引用、已有指针
    MyString & operator=(const MyString & other){
        if(&other==this){
            return *this;
        }
        if(p){
            delete [] p;
        }
        if(other.p){
            p=new char[strlen(other.p)+1];
            strcpy(p,other.p);
        }
        else {
            p=NULL;
        }
        return *this;
    }

    //对输入输出流重载的写法
    friend ostream & operator<<(ostream & out,const MyString &s){
        out<<s.p;
        return out;
    }
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}