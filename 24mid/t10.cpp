#include<bits/stdc++.h>
using namespace std;
map<string,int> value;
map<string,int> num;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        string s;
        int v,n;
        cin>>s>>v>>n;
        num[s]=n;
        value[s]=v;
    }
    int ans=0;
    for(int i=0;i<3*m;i++){
        string s;
        cin>>s;
        if(num[s]>0){
            num[s]--;
            ans+=value[s];
        }
    }
    cout<<ans;
    return 0;
}