#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
// 在此处补充你的代码
    private:
        int score1,score2,score3,score4;
        double avg_score;
        int age;
        int ID;
        string name;
    public:
        void input(){
            string inp;
            getline(cin,inp);
            string tmp;
            stringstream ss(inp);
            getline(ss,name,',');
            getline(ss,tmp,',');
            age=stoi(tmp);
            getline(ss,tmp,',');
            ID=stoi(tmp);
            getline(ss,tmp,',');
            score1=stoi(tmp);
            getline(ss,tmp,',');
            score2=stoi(tmp);
            getline(ss,tmp,',');
            score3=stoi(tmp);
            getline(ss,tmp,',');
            score4=stoi(tmp);
        }
        void calculate(){
            avg_score=(score1+score2+score3+score4)/4.0;
        }
        void output(){
            cout<<name<<','<<age<<','<<ID<<','<<avg_score<<endl;
        }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}