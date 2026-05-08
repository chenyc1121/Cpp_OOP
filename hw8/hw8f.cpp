#include<bits/stdc++.h>
using namespace std;
map<int,int> members;
int n;
int main(){
    cin>>n;
    members.insert(make_pair(1000000000,1));
    for(int i=0;i<n;i++){
        int id,v;
        cin>>id>>v;
        auto it=members.lower_bound(v);
        if(it==members.begin()){
            cout<<id<<" "<<it->second<<endl;
        }
        else if(it==members.end()){
            cout<<id<<" "<<members.rbegin()->second<<endl;
        }
        else {
            if(it->first-v>v-prev(it)->first){
                cout<<id<<" "<<prev(it)->second<<endl;
            }
            else if(it->first-v<v-prev(it)->first){
                cout<<id<<" "<<it->second<<endl;
            }
            else {
                if(prev(it)->second>it->second){
                    cout<<id<<" "<<it->second<<endl;
                }
                else {
                    cout<<id<<" "<<prev(it)->second<<endl;
                }
            }
        }
        if(members.find(v)!=members.end()){
            if(id<members.find(v)->second){
                members.find(v)->second=id;
            }
        }
        else members.insert(make_pair(v,id));
    }
    return 0;
}