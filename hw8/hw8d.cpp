#include<bits/stdc++.h>
using namespace std;
vector<string> vecstr;
bool isnum(string s){
    if(s.length()>5)return false;
    for(char c:s){
        if(!isdigit(c))return false;
    }
    int val=stoi(s);
    return val>=0&&val<=99999;
}

string get_string();
int get_int();

string get_string(){
    string opt;
    cin>>opt;
    if(opt=="copy"){
        int n=get_int();
        int x=get_int();
        int l=get_int();
        return vecstr[n-1].substr(x,l);
    }
    else if(opt=="add"){
        string s1=get_string();
        string s2=get_string();
        if(isnum(s1)&&isnum(s2)){
            return to_string(stoi(s1)+stoi(s2));
        }
        else return s1+s2;
    }
    else return opt;
}
int get_int(){
    string opt;
    cin>>opt;
    if(opt=="find"){
        string s=get_string();
        int n=get_int();
        if(vecstr[n-1].find(s)==string::npos){
            return vecstr[n-1].length();
        }
        else return vecstr[n-1].find(s);
    }
    else if(opt=="rfind"){
        string s=get_string();
        int n=get_int();
        if(vecstr[n-1].rfind(s)==string::npos){
            return vecstr[n-1].length();
        }
        else return vecstr[n-1].rfind(s);
    }
    else return stoi(opt);
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        vecstr.push_back(s);
    }
    string opt;
    while(cin>>opt&&opt!="over"){
        if(opt=="insert"){
            string s=get_string();
            int n=get_int();
            int x=get_int();
            vecstr[n-1].insert(x,s);
        }
        else if(opt=="reset"){
            string s=get_string();
            int n=get_int();
            vecstr[n-1]=s;
        }
        else if(opt=="print"){
            int n=get_int();
            cout<<vecstr[n-1]<<endl;
        }
        else if(opt=="printall"){
            for(int i=0;i<vecstr.size();i++){
                cout<<vecstr[i]<<endl;
            }
        }
    }
    return 0;
}