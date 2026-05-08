#include<iostream>
#include<queue>
#include<string>
using namespace std;
struct warrior
{
    /* data */
    int v;
    string name;
};
class cmp{
    public:
bool operator()(warrior& x,warrior& y){
    return x.v<y.v;
}
};
priority_queue<warrior,vector<warrior>,cmp> p;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int v;string s;
        cin>>v>>s;
        p.push(warrior{v,s});
    }
    while(!p.empty()){
        if(p.size()==1){
            cout<<p.top().name;
            return 0;
        }
        warrior x=p.top();p.pop();
        warrior y=p.top();p.pop();
        if(x.v>y.v){
            p.push({x.v-y.v,x.name});
        }
    }
    cout<<-1;
    return 0;
}
