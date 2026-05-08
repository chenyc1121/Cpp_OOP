#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

// 阵营编号：0 表示 red，1 表示 blue。
enum Camp { RED, BLUE };

// 两个阵营的造兵顺序：
// RED : iceman, lion, wolf, ninja, dragon
// BLUE: lion, dragon, ninja, iceman, wolf
int warrior_order[2][5]={{2,3,4,1,0},{3,0,1,2,4}};

// 输入的武士生命值（造兵消耗），下标顺序为：
// dragon, ninja, iceman, lion, wolf
int warrior_original_hp[5];

// 输出时用到的名称表。
string headquarter_name[2]={"red","blue"};
string warrior_name[5]={"dragon","ninja","iceman","lion","wolf"};
string weapon_name[3]={"sword", "bomb","arrow"};

// 武士基类。
class warriors{
    protected:
        int id;
        Camp side;
        vector<int> weapon;
        int hp;
        warriors(int tid,Camp tside,int thp):id(tid),side(tside),hp(thp){}
    public:
    // 各个子类可重写：输出出生时的附加信息。
    virtual void out_born(){    }
};

// dragon：一件武器 + 士气。
class dragon:public warriors{
    double morale;
    public:
    dragon(int n,Camp side,int self_hp,int rest_hp):warriors(n,side,self_hp),morale(rest_hp/(double)self_hp){
        weapon.push_back(n%3);
    }
    double get_morale(){
        return morale;
    }
    void out_born(){
        cout<<"It has a "<<weapon_name[weapon[0]]<<",and it's morale is "<<fixed<<setprecision(2)<<morale<<endl;
    }
};

// ninja：两件武器。
class ninja:public warriors{
    public:
    ninja(int n,Camp side,int self_hp):warriors(n,side,self_hp){
        weapon.push_back(n%3);
        weapon.push_back((n+1)%3);
    }
    void out_born(){
        cout<<"It has a "<<weapon_name[weapon[0]]<<" and a "<<weapon_name[weapon[1]]<<endl;
    }
};

// iceman：一件武器。
class iceman:public warriors{
    public:
    iceman(int n,Camp side,int self_hp):warriors(n,side,self_hp){
        weapon.push_back(n%3);
    }
    void out_born(){
        cout<<"It has a "<<weapon_name[weapon[0]]<<endl;
    }
};

// lion：没有武器附加行，但有忠诚度。
class lion:public warriors{
    int loyalty;
    public:
    lion(int n,Camp side,int self_hp,int rest_hp):warriors(n,side,self_hp),loyalty(rest_hp){}
    int get_loyalty(){
        return loyalty;
    }
    void out_born(){
        cout<<"It's loyalty is "<<loyalty<<endl;
    }
};

// wolf：本题中没有额外出生输出。
class wolf:public warriors{
    public:
    wolf(int n,Camp side,int self_hp):warriors(n,side,self_hp){}
};

// 司令部类：管理生命元、造兵指针和已生产武士。
class headquarter{
    int totalhp;
    int next_idx;
    int num;
    int cnt_warrior[5];
    bool ismaking;
    Camp side;
    vector<warriors*> army;
    public:
    headquarter(int origin_hp,Camp side):totalhp(origin_hp),side(side),num(0),next_idx(0),cnt_warrior({0}),ismaking(true){}

    // 从当前 next_idx 出发，偏移 i 位置来生产一个武士。
    void make_warrior(int i){
        num++;
        int nextwarrior=warrior_order[side][(next_idx+i)%5];//按dragon 、ninja、iceman、lion、wolf的顺序
        totalhp-=warrior_original_hp[nextwarrior];
        cnt_warrior[nextwarrior]++;
        cout<<" "<<headquarter_name[side]<<" "<<warrior_name[nextwarrior]<<" "<<num<<" born with strength "<<warrior_original_hp[nextwarrior]<<",";
        cout<<cnt_warrior[nextwarrior]<<" "<<warrior_name[nextwarrior]<<" in "<<headquarter_name[side]<<" headquarter"<<endl;
        switch(nextwarrior){
            case 0:{
                army.push_back(new dragon(num,side,warrior_original_hp[nextwarrior],totalhp));
                break;
            }
            case 1:{
                army.push_back(new ninja(num,side,warrior_original_hp[nextwarrior]));
                break;
            }
            case 2:{
                army.push_back(new iceman(num,side,warrior_original_hp[nextwarrior]));
                break;
            }
            case 3:{
                army.push_back(new lion(num,side,warrior_original_hp[nextwarrior],totalhp));
                break;
            }
            case 4:{
                army.push_back(new wolf(num,side,warrior_original_hp[nextwarrior]));
                break;
            }
        }
        // 输出该武士类型对应的第二行附加信息。
        army[num-1]->out_born();
    }

    // 标记该司令部停止生产。
    void stop_make_warrior(){
        cout<<" "<<headquarter_name[side]<<" headquarter stops making warriors"<<endl;
        ismaking=false;
    }
    int get_hp(){
        return totalhp;
    }
    int get_next_idx(){
        return next_idx;
    }
    void set_next_idx(int i){
        next_idx=i;
    }
    bool check(){
        return ismaking;
    }
    int get_camp(){
        return side;
    }
};

// 按题意模拟所有测试用例。
int main(){
    int T;
    cin>>T;
    for(int c=1;c<=T;c++){
        cout<<"Case:"<<c<<endl;
        int m;
        cin>>m;
        for(int i=0;i<5;i++){
            cin>>warrior_original_hp[i];
        }
        headquarter red_quarter(m,RED);
        headquarter blue_quarter(m,BLUE);
        int t=0;
        while (true){
            // 双方都停止生产后结束模拟。
            if((!red_quarter.check())&&(!blue_quarter.check())){
                break;
            }

            // 每个整点先处理红方。
            if(red_quarter.check()){
                int st_idx=red_quarter.get_next_idx();
                int hp=red_quarter.get_hp();
                cout << setw(3) << setfill('0') <<t;
                // 按循环顺序最多尝试 5 种武士。
                for(int i=0;i<5;i++){
                    int next_idx=(st_idx+i)%5;
                    if(warrior_original_hp[warrior_order[RED][next_idx]]<=hp){
                        red_quarter.make_warrior(i);
                        red_quarter.set_next_idx((next_idx+1)%5);
                        break;
                    }
                    // 5 种都造不起，则红方停止生产。
                    if(i==4){
                        red_quarter.stop_make_warrior();
                    }
                }
            }

            // 同一整点再处理蓝方。
            if(blue_quarter.check()){
                int st_idx=blue_quarter.get_next_idx();
                int hp=blue_quarter.get_hp();
                cout << setw(3) << setfill('0') <<t;
                for(int i=0;i<5;i++){
                    int next_idx=(st_idx+i)%5;
                    if(warrior_original_hp[warrior_order[BLUE][next_idx]]<=hp){
                        blue_quarter.make_warrior(i);
                        blue_quarter.set_next_idx((next_idx+1)%5);
                        break;
                    }
                    if(i==4){
                        blue_quarter.stop_make_warrior();
                    }
                }
            }
            t++;
        }
    }
    return 0;
}