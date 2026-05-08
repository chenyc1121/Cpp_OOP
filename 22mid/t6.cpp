#include <set>
#include <iostream>
using namespace std;
template <class T>
class MySet: public set<T> {
public:
// 在此处补充你的代码
    void insert(T w){
        bool flag=this->set<T>::insert(w).second;
        if(!flag)cout<<"Error insert "<<w<<endl;
    }
    void erase(T w){
        if(this->set<T>::erase(w)==0){
            cout<< "Error erase "<<w<<endl;
        }
    }
};
int main(){
	int n; scanf("%d",&n);
	MySet<int> S;
	for (int i=1;i<=n;i++){
		cout<<"Operation #"<<i<<":"<<endl;
		string type; int w;
		cin>>type>>w;
		if (type=="insert") S.insert(w);
		else if (type=="erase") S.erase(w);
	}
	cout<<endl;
	MySet<string> S2;
	for (int i=1;i<=n;i++){
		cout<<"Operation #"<<i<<":"<<endl;
		string type; string w;
		cin>>type>>w;
		if (type=="insert") S2.insert(w);
		else if (type=="erase") S2.erase(w);
	}
}