#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class cat{
    public:
    int old;
    cat(int o):old(o){}
    virtual int value()const{
        return old*50;
    }
    virtual void Print(){
        cout<<"cat "<<old<<endl;
    }
};
class drug_cat:public cat{
    public:
    int drug;
    drug_cat(int o,int d):cat(o),drug(d){}
    int value()const{
        return old*50+drug;
    }
    void Print(){
        cout<<"drug_cat "<<old<<" "<<drug<<endl;
    }
};
class Comp{
    public:
    bool operator()(const cat* a,const cat* b)const{
        return a->value()<b->value();
    }
};
void Print(cat* p){
    p->Print();
}
int main()
{
    int t, d;
    cin >> t;
    set<cat*, Comp> ct;
    while (t--) {
        int n;
        cin >> n;
        ct.clear();
        for (int i = 0; i < n; ++i) {
            string c; int k;
            cin >> c >> k;

            if (c == "cat")
                ct.insert(new cat(k));
            else{
                cin >> d;
                ct.insert(new drug_cat(k, d));
                }
        }
        for_each(ct.begin(), ct.end(), Print);
        cout << "---" << endl;
    }
    return 0;
}