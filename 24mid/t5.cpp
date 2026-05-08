#include <iostream>
#include <algorithm>
#include <cmath>
#include<vector>
using namespace std;
int n;
int main()
{
  int n,m;
  cin >> n >> m;
  vector<int> v; 
  for(int i= 0;i < n; ++i) {
    int a;
    cin >> a;
    v.push_back(a);
  }
  auto f =[=](int x,int y){
    if(abs(x-m)==abs(y-m))return x<y;
    else return abs(x-m)<abs(y-m);
  };
// 在此处补充你的代码
sort(v.begin(),v.end(),f);

  for(int x:v)
    cout << x << " ";
  return 0;
}