#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;

class MyMap:public map<int,priority_queue<string,vector<string>,greater<string> >,greater<int> >{
// 在此处补充你的代码
    friend istream& operator>>(istream& in,MyMap& m){
        string s;int v;
        cin>>s>>v;
        m[v].push(s);
        return in;
    }
    friend ostream& operator<<(ostream& out,MyMap& m){
        for(auto& p:m){
            cout<<p.first;
            string las;
            while(!p.second.empty()){
                string name=p.second.top();p.second.pop();
                if(name!=las){
                    cout<<" "<<name;
                }
                las=name;
            }
            cout<<endl;
        }
        return out;
    }
};
int main()
{
    int n;
    cin >> n;
    MyMap mm;
    for (int i = 0; i < n; ++i)
        cin >> mm;
    cout<<mm;
	return 0; 
}