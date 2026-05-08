#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
int main(){
    int x,p;
    cin>>x>>p; //保证 x 有逆元
    int a[10]={0,1,2,3,4,9,8,7,6,5};
    sort(a,a+10,[=](int u,int v){
        if(u*x%p==v*x%p)return u<v;
        else return u*x%p<v*x%p;
    }
// 在此处补充你的代码
); 

    for(int i=0;i<10;i++)cout<<a[i]<<endl;
}