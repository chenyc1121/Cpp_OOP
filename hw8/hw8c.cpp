#include<iostream>
#include<set>
#include<string>
using namespace std;
multiset<int> intset;
set<int> added;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string s;int v;
        cin>>s>>v;
        if(s=="add"){
            intset.insert(v);
            added.insert(v);
            cout<<intset.count(v)<<endl;
        }
        else if(s=="del"){
            cout<<intset.count(v)<<endl;
            intset.erase(v);
        }
        else{
            if(added.find(v)==added.end()){
                cout<<"0 ";
            }
            else cout<<"1 ";
            cout<<intset.count(v)<<endl;
        }
    }
    return 0;
}