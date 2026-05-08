#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<cmath>
using namespace std;
int n;
priority_queue<double,vector<double>,greater<double> > memo;
stack<double> st;

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        double tmp;
        scanf("%lf",&tmp);
        memo.push(tmp);
    }
    char s[25];
    while(scanf("%s",s)!=EOF){
        double x,y;
        switch(s[0])
        {
            case('='):
                memo.pop();
                printf("%e\n",st.top());
                memo.push(st.top());
                st.pop();
                break;
            case('+'):
                x=st.top();st.pop();
                y=st.top();st.pop();
                st.push(x+y);
                break;
            case('-'):
                x=st.top();st.pop();
                y=st.top();st.pop();
                st.push(y-x);
                break;
            case('*'):
                x=st.top();st.pop();
                y=st.top();st.pop();
                st.push(x*y);
                break;
            case('/'):
                x=st.top();st.pop();
                y=st.top();st.pop();
                st.push(y/x);
                break;
            case('^'):
                x=st.top();st.pop();
                y=st.top();st.pop();
                st.push(pow(y,x));
                break;
            default:
                st.push(stod(s));
        }
    }
    printf("\n");
    printf("%e ",memo.top());
    memo.pop();
    while(!memo.empty()){
        double out=memo.top();
        memo.pop();
        printf(" %e",out);
    }
    return 0;
}