#include <iostream>
#include <string>
using namespace std;

template <class T>
void print(T a) {
    cout << a << endl;
}

class MyString {
public:
    string m_data;
    MyString(string a) : m_data(a) {}
// 在此处补充你的代码
    friend ostream& operator<<(ostream& out,MyString& s){
        out<<s.m_data;
        return out;
    }
    string operator+(MyString other){
        return m_data+other.m_data;
    }
};
template <typename T>
class MyTemplateClass{
    public:
    T v;
    MyTemplateClass(const T& v):v(v){    }
    operator T(){
        return v;
    }
    friend ostream& operator<<(ostream& out,MyTemplateClass& s){
        out<<s.v+s.v;
        return out;
    }
};
int main()
{
    int m;
    int num;
    string str;
    cin >> m;
    for (; m>0; m--) {
        cin >> num >> str;
        MyTemplateClass<int> obj(num);
        print(int(obj));
        print(obj);
        MyTemplateClass<MyString> obj2(str);
        print(MyString(obj2));
        print(obj2);
    }
}