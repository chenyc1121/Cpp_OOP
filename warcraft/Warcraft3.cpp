#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<tuple>
using namespace std;
const int Inf=1e6;
// 阵营编号：0 表示 red，1 表示 blue。
enum Camp { RED, BLUE };

// 两个阵营的造兵顺序：
// RED : iceman, lion, wolf, ninja, dragon
// BLUE: lion, dragon, ninja, iceman, wolf
int warrior_order[2][5]={{2,3,4,1,0},{3,0,1,2,4}};

// 输入的武士生命值（造兵消耗），下标顺序为：
// dragon, ninja, iceman, lion, wolf
int warrior_original_hp[5];
int warrior_original_atk[5];

// 输出时用到的名称表。
string headquarter_name[2]={"red","blue"};

int headquarter_pos[2];
int city[30];
vector<tuple<int,int,int> > yelled;

class warriors; // 前向声明

struct City {
    warriors* red_w = nullptr;
    warriors* blue_w = nullptr;
} cities[25];  // 0 是红方司令部，N+1 是蓝方司令部

int global_t = 0;
int loyalty_decay_global = 0;

class weapon{
        const string name;
        int num;
    protected:
        int life;
    public:
        weapon(string s,int tnum,int ori_life=Inf):name(s),life(ori_life),num(tnum){}
        virtual void attack(warriors&me,warriors&other);
        string get_name(){
            return name;
        }
        bool can_use(){
            return life>0;
        }
        static bool cmp_fight(weapon* self,weapon* other){
            if(self->name=="arrow"&&other->name=="arrow"){
                return self->life<other->life;
            }
            else{
                return self->num<other->num;
            }
        }
        static bool cmp_rob(weapon* self,weapon* other){
            if(self->name=="arrow"&&other->name=="arrow"){
                return self->life>other->life;
            }
            else{
                return self->num<other->num;
            }
        }
};
class sword:public weapon{
    public:
        sword():weapon("sword",0){}
        void attack(warriors&me,warriors&other);
};
class bomb:public weapon{
    public:
        bomb():weapon("bomb",1,1){}
        void attack(warriors&me,warriors&other);
};
class arrow:public weapon{
    public:
        arrow():weapon("arrow",2,2){}
        void attack(warriors&me,warriors&other);
};



// 武士基类。
class warriors{
    friend class wolf; 
    protected:
        string name;
        int id;
        Camp side;
        vector<weapon*> myweapon;
        int hp;
        int atk;
        int pos;
        warriors(int tid,Camp tside,int thp,int tatk,string s,int p):id(tid),side(tside),hp(thp),atk(tatk),name(s),pos(p){    }
    public:
    // 各个子类可重写：输出出生时的附加信息。
    virtual void out_born(){    }
    int& get_atk(){
        return atk;
    }
    int& get_hp(){
        return hp;
    }
    int get_id(){
        return id;
    }
    Camp get_side(){
        return side;
    }
    int& get_pos(){
        return pos;
    }
    string get_name(){
        return name;
    }
    bool reached(){
        return pos==headquarter_pos[(side+1)%2];
    }
    void have_weapon(int n){
        switch (n%3)
        {
        case 0:
            myweapon.push_back(new sword());
            break;
        case 1:
            myweapon.push_back(new bomb());
            break;
        case 2:
            myweapon.push_back(new arrow());
            break;
        default:
            break;
        }
    }
    bool attack(warriors& other,int i){
        myweapon[i]->attack(*this,other);
        return other.get_hp()<=0;
    }
    bool died(){
        return hp<=0;
    }
    virtual void take_weapons(warriors& other){
        sort(other.myweapon.begin(),other.myweapon.end(),weapon::cmp_rob);
        for(int i=0;i<other.myweapon.size();i++){
            if(myweapon.size()>=10)return;
            myweapon.push_back(other.myweapon[i]);
        }
    }
    virtual void rob(warriors& other) {}
    
    static void fight(warriors& red, warriors& blue, int k) {
        warriors* fir = (k % 2 == 1) ? &red : &blue;
        warriors* sec = (k % 2 == 1) ? &blue : &red;
        sort(fir->myweapon.begin(), fir->myweapon.end(), weapon::cmp_fight);
        sort(sec->myweapon.begin(), sec->myweapon.end(), weapon::cmp_fight);

        int fir_idx = 0, sec_idx = 0;
        int max_rounds = 0;
        int prev_fir_hp = fir->get_hp();
        int prev_sec_hp = sec->get_hp();
        int unchanged_cycles = 0;
        while(true) {
            if (fir->get_hp() == prev_fir_hp && sec->get_hp() == prev_sec_hp) {
                unchanged_cycles++;
                if (unchanged_cycles > 100) break; // tie
            } else {
                unchanged_cycles = 0;
                prev_fir_hp = fir->get_hp();
                prev_sec_hp = sec->get_hp();
            }
            
            bool fir_has = false, sec_has = false;
            for(auto w : fir->myweapon) if(w->can_use()) { fir_has=true; break; }
            for(auto w : sec->myweapon) if(w->can_use()) { sec_has=true; break; }
            
            if(!fir_has && !sec_has) break;
            
            if(fir_has) {
                while(!fir->myweapon[fir_idx]->can_use()) fir_idx = (fir_idx + 1) % fir->myweapon.size();
                fir->attack(*sec, fir_idx);
                fir_idx = (fir_idx + 1) % fir->myweapon.size();
                if(fir->died() || sec->died()) break;
            }
            if(sec_has) {
                while(!sec->myweapon[sec_idx]->can_use()) sec_idx = (sec_idx + 1) % sec->myweapon.size();
                sec->attack(*fir, sec_idx);
                sec_idx = (sec_idx + 1) % sec->myweapon.size();
                if(fir->died() || sec->died()) break;
            }
        }

        fir->myweapon.erase(remove_if(fir->myweapon.begin(), fir->myweapon.end(), [](weapon* w){ return !w->can_use(); }), fir->myweapon.end());
        sec->myweapon.erase(remove_if(sec->myweapon.begin(), sec->myweapon.end(), [](weapon* w){ return !w->can_use(); }), sec->myweapon.end());

        if (red.died() && blue.died()) {
            cout << setw(3) << setfill('0') << global_t << ":40 both red " << red.get_name() << " " << red.get_id() << " and blue " << blue.get_name() << " " << blue.get_id() << " died in city " << k << endl;
        } else if (red.died()) {
            cout << setw(3) << setfill('0') << global_t << ":40 blue " << blue.get_name() << " " << blue.get_id() << " killed red " << red.get_name() << " " << red.get_id() << " in city " << k << " remaining " << blue.get_hp() << " elements" << endl;
            blue.take_weapons(red);
        } else if (blue.died()) {
            cout << setw(3) << setfill('0') << global_t << ":40 red " << red.get_name() << " " << red.get_id() << " killed blue " << blue.get_name() << " " << blue.get_id() << " in city " << k << " remaining " << red.get_hp() << " elements" << endl;
            red.take_weapons(blue);
        } else {
            cout << setw(3) << setfill('0') << global_t << ":40 both red " << red.get_name() << " " << red.get_id() << " and blue " << blue.get_name() << " " << blue.get_id() << " were alive in city " << k << endl;
        }

        if (red.get_name() == "dragon" && !red.died()) cout << setw(3) << setfill('0') << global_t << ":40 red dragon " << red.get_id() << " yelled in city " << k << endl;
        if (blue.get_name() == "dragon" && !blue.died()) cout << setw(3) << setfill('0') << global_t << ":40 blue dragon " << blue.get_id() << " yelled in city " << k << endl;
    }

    void report() {
        int s=0, b=0, a=0;
        for(auto wp: myweapon) {
            if(!wp->can_use()) continue; // extra safety
            if(wp->get_name()=="sword") s++;
            else if(wp->get_name()=="bomb") b++;
            else if(wp->get_name()=="arrow") a++;
        }
        cout << setw(3) << setfill('0') << global_t << ":55 " << headquarter_name[side] << " " << name << " " << id 
             << " has " << s << " sword " << b << " bomb " << a << " arrow and " << hp << " elements" << endl;
    }
};

// dragon：一件武器 + 士气。
class dragon:public warriors{
    double morale;
    public:
    dragon(int n,Camp side,int self_hp,int rest_hp,int atk,int p):warriors(n,side,self_hp,atk,"dragon",p),morale(rest_hp/(double)self_hp){
        have_weapon(n);
    }
    double get_morale(){
        return morale;
    }
    void out_born(){
        cout<<setw(3)<<setfill('0')<<global_t<<":00 "<<headquarter_name[side]<<" "<<name<<" "<<id<<" born"<<endl;
    }
};

// ninja：两件武器。
class ninja:public warriors{
    public:
    ninja(int n,Camp side,int self_hp,int atk,int p):warriors(n,side,self_hp,atk,"ninja",p){
        have_weapon(n);
        have_weapon(n+1);
    }
    void out_born(){
        cout<<setw(3)<<setfill('0')<<global_t<<":00 "<<headquarter_name[side]<<" "<<name<<" "<<id<<" born"<<endl;
    }
};

// iceman：一件武器。
class iceman:public warriors{
    public:
    iceman(int n,Camp side,int self_hp,int atk,int p):warriors(n,side,self_hp,atk,"iceman",p){
        have_weapon(n);
    }
    void out_born(){
        cout<<setw(3)<<setfill('0')<<global_t<<":00 "<<headquarter_name[side]<<" "<<name<<" "<<id<<" born"<<endl;
    }
};

// lion：没有武器附加行，但有忠诚度。
class lion:public warriors{
    int loyalty;
    public:
    lion(int n,Camp side,int self_hp,int rest_hp,int atk,int p):warriors(n,side,self_hp,atk,"lion",p),loyalty(rest_hp){
        have_weapon(n);
    }
    int& get_loyalty(){
        return loyalty;
    }
    void run_away(){
        if(reached())return;
        if(loyalty<=0){
            cout<<setw(3)<<setfill('0')<<global_t<<":05 "<<headquarter_name[side]<<" lion "<<id<<" ran away"<<endl;
            hp=0;
        }
    }
    void out_born(){
        cout<<setw(3)<<setfill('0')<<global_t<<":00 "<<headquarter_name[side]<<" "<<name<<" "<<id<<" born"<<endl;
        cout<<"Its loyalty is "<<loyalty<<endl;
    }
};

// wolf：本题中没有额外出生输出。
class wolf:public warriors{
    public:
    wolf(int n,Camp side,int self_hp,int atk,int p):warriors(n,side,self_hp,atk,"wolf",p){}
    void out_born(){
        cout<<setw(3)<<setfill('0')<<global_t<<":00 "<<headquarter_name[side]<<" "<<name<<" "<<id<<" born"<<endl;
    }
    void rob(warriors& other){  
        if (other.get_name() == "wolf" || other.myweapon.empty()) return;
        sort(other.myweapon.begin(),other.myweapon.end(),weapon::cmp_rob);
        int cnt=0;
        for(int i=0;i<other.myweapon.size();i++){
            if(myweapon.size()>=10)break;
            if(other.myweapon[i]->get_name()!=other.myweapon[0]->get_name())break;
            myweapon.push_back(other.myweapon[i]);
            cnt++;
        }
        if(cnt){
            cout<<setw(3)<<setfill('0')<<global_t<<":35 "<<headquarter_name[side]<<" wolf "<<id<<" took "<<cnt<<" "<<other.myweapon[0]->get_name()<<" from "<<headquarter_name[1-side]<<" "<<other.get_name()<<" "<<other.get_id()<<" in city "<<pos<<endl;
            other.myweapon.erase(other.myweapon.begin(), other.myweapon.begin() + cnt);
        }
    }
};

// 司令部类：管理生命元、造兵指针和已生产武士。
class headquarter{
    int totalhp;
    int next_idx;
    int num;
    int cnt_warrior[5];
    bool ismaking;
    Camp side;
    public:
    int pos;
    headquarter(int origin_hp,Camp side,int p):totalhp(origin_hp),side(side),num(0),next_idx(0),cnt_warrior{0},ismaking(true),pos(p){}

    // 从当前 next_idx 出发，偏移 i 位置来生产一个武士。
    warriors* make_warrior(int i){
        num++;
        int nextwarrior=warrior_order[side][(next_idx+i)%5];//按dragon 、ninja、iceman、lion、wolf的顺序
        totalhp-=warrior_original_hp[nextwarrior];
        cnt_warrior[nextwarrior]++;
        //cout<<" "<<headquarter_name[side]<<" "<<warrior_name[nextwarrior]<<" "<<num<<" born with strength "<<warrior_original_hp[nextwarrior]<<",";
        //cout<<cnt_warrior[nextwarrior]<<" "<<warrior_name[nextwarrior]<<" in "<<headquarter_name[side]<<" headquarter"<<endl;
        warriors* new_w = nullptr;
        switch(nextwarrior){
            case 0: new_w = new dragon(num,side,warrior_original_hp[nextwarrior],totalhp,warrior_original_atk[nextwarrior],pos); break;
            case 1: new_w = new ninja(num,side,warrior_original_hp[nextwarrior],warrior_original_atk[nextwarrior],pos); break;
            case 2: new_w = new iceman(num,side,warrior_original_hp[nextwarrior],warrior_original_atk[nextwarrior],pos); break;
            case 3: new_w = new lion(num,side,warrior_original_hp[nextwarrior],totalhp,warrior_original_atk[nextwarrior],pos); break;
            case 4: new_w = new wolf(num,side,warrior_original_hp[nextwarrior],warrior_original_atk[nextwarrior],pos); break;
        }
        // 输出该武士类型对应的第二行附加信息。
        new_w->out_born();
        return new_w;
    }

    // 标记该司令部停止生产。
    void stop_make_warrior(){
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

void weapon::attack(warriors&me,warriors&other) {}
void sword::attack(warriors&me,warriors&other) {
    other.get_hp() -= me.get_atk() * 2 / 10;
}
void bomb::attack(warriors&me,warriors&other) {
    other.get_hp() -= me.get_atk() * 4 / 10;
    if(me.get_name() != "ninja") {
        me.get_hp() -= (me.get_atk() * 4 / 10) / 2;
    }
    life--;
}
void arrow::attack(warriors&me,warriors&other) {
    other.get_hp() -= me.get_atk() * 3 / 10;
    life--;
}

// 按题意模拟所有测试用例。
int main(){
    int T;
    cin>>T;
    for(int c=1;c<=T;c++){
        cout<<"Case "<<c<<":"<<endl;
        int total_hp,city_num,loyalty_decay,end_time;
        cin>>total_hp>>city_num>>loyalty_decay>>end_time;
        for(int i=0;i<5;i++){
            cin>>warrior_original_hp[i];
        }
        for(int i=0;i<5;i++){
            cin>>warrior_original_atk[i];
        }
        headquarter_pos[RED]=0;
        headquarter_pos[BLUE]=city_num+1;
        headquarter red_quarter(total_hp,RED,0);
        headquarter blue_quarter(total_hp,BLUE,city_num+1);
        
        loyalty_decay_global = loyalty_decay;
        
        for(int i=0; i<25; i++) {
            if (cities[i].red_w) { delete cities[i].red_w; cities[i].red_w = nullptr; }
            if (cities[i].blue_w) { delete cities[i].blue_w; cities[i].blue_w = nullptr; }
        }
        
        int t = 0;
        bool game_over = false;
        while (!game_over) {
            global_t = t;
            for(int mi=0; mi<=55; mi+=5){
                if (t * 60 + mi > end_time) {
                    game_over = true;
                    break;
                }
                
                if(mi==0){
                    if(red_quarter.check()){
                        int st_idx=red_quarter.get_next_idx();
                        int hp=red_quarter.get_hp();
                        int next_idx = st_idx;
                        if(warrior_original_hp[warrior_order[RED][next_idx]] <= hp){
                            cities[0].red_w = red_quarter.make_warrior(0);
                            red_quarter.set_next_idx((next_idx+1)%5);
                        } else {
                            red_quarter.stop_make_warrior();
                        }
                    }
                    if(blue_quarter.check()){
                        int st_idx=blue_quarter.get_next_idx();
                        int hp=blue_quarter.get_hp();
                        int next_idx = st_idx;
                        if(warrior_original_hp[warrior_order[BLUE][next_idx]] <= hp){
                            cities[city_num+1].blue_w = blue_quarter.make_warrior(0);
                            blue_quarter.set_next_idx((next_idx+1)%5);
                        } else {
                            blue_quarter.stop_make_warrior();
                        }
                    }
                }

                if(mi==5){
                    for(int i=0;i<=city_num+1;i++){
                        if(cities[i].red_w && cities[i].red_w->get_name()=="lion"){
                            lion* l = (lion*)cities[i].red_w;
                            if(!l->reached() && l->get_loyalty() <= 0){
                                l->run_away();
                                delete cities[i].red_w;
                                cities[i].red_w = nullptr;
                            }
                        }
                        if(cities[i].blue_w && cities[i].blue_w->get_name()=="lion"){
                            lion* l = (lion*)cities[i].blue_w;
                            if(!l->reached() && l->get_loyalty() <= 0){
                                l->run_away();
                                delete cities[i].blue_w;
                                cities[i].blue_w = nullptr;
                            }
                        }
                    }
                }

                if(mi==10){
                    warriors* next_red[25] = {nullptr};
                    warriors* next_blue[25] = {nullptr};

                    for(int i=0; i<=city_num+1; i++) {
                        if(cities[i].red_w) {
                            warriors* w = cities[i].red_w;
                            if(w->reached()) { next_red[i] = w; continue; }
                            w->get_pos()++;
                            if(w->get_name() == "iceman") w->get_hp() -= w->get_hp() / 10;
                            if(w->get_name() == "lion") ((lion*)w)->get_loyalty() -= loyalty_decay_global;
                            next_red[w->get_pos()] = w;
                        }
                    }
                    for(int i=city_num+1; i>=0; i--) {
                        if(cities[i].blue_w) {
                            warriors* w = cities[i].blue_w;
                            if(w->reached()) { next_blue[i] = w; continue; }
                            w->get_pos()--;
                            if(w->get_name() == "iceman") w->get_hp() -= w->get_hp() / 10;
                            if(w->get_name() == "lion") ((lion*)w)->get_loyalty() -= loyalty_decay_global;
                            next_blue[w->get_pos()] = w;
                        }
                    }
                    
                    for(int i=0; i<=city_num+1; i++) {
                        cities[i].red_w = next_red[i];
                        cities[i].blue_w = next_blue[i];
                    }
                    
                    bool taken = false;
                    for(int i=0; i<=city_num+1; i++) {
                        if (cities[i].red_w && (!cities[i].red_w->reached() || i == city_num + 1) && cities[i].red_w->get_pos() != 0) {
                            warriors* w = cities[i].red_w;
                            cout << setw(3) << setfill('0') << t << ":10 red " << w->get_name() << " " << w->get_id();
                            if (w->get_pos() == city_num + 1) {
                                cout << " reached blue headquarter with " << w->get_hp() << " elements and force " << w->get_atk() << endl;
                                cout << setw(3) << setfill('0') << t << ":10 blue headquarter was taken" << endl;
                                taken = true;
                            } else {
                                cout << " marched to city " << w->get_pos() << " with " << w->get_hp() << " elements and force " << w->get_atk() << endl;
                            }
                        }
                        if (cities[i].blue_w && (!cities[i].blue_w->reached() || i == 0) && cities[i].blue_w->get_pos() != city_num + 1) {
                            warriors* w = cities[i].blue_w;
                            cout << setw(3) << setfill('0') << t << ":10 blue " << w->get_name() << " " << w->get_id();
                            if (w->get_pos() == 0) {
                                cout << " reached red headquarter with " << w->get_hp() << " elements and force " << w->get_atk() << endl;
                                cout << setw(3) << setfill('0') << t << ":10 red headquarter was taken" << endl;
                                taken = true;
                            } else {
                                cout << " marched to city " << w->get_pos() << " with " << w->get_hp() << " elements and force " << w->get_atk() << endl;
                            }
                        }
                    }
                    if (taken) {
                        game_over = true;
                        break;
                    }
                }

                if(mi==35){
                    for(int i=1; i<=city_num; i++){
                        if(cities[i].red_w && cities[i].blue_w) {
                            if(cities[i].red_w->get_name() == "wolf" && cities[i].blue_w->get_name() != "wolf") {
                                cities[i].red_w->rob(*cities[i].blue_w);
                            } else if (cities[i].blue_w->get_name() == "wolf" && cities[i].red_w->get_name() != "wolf") {
                                cities[i].blue_w->rob(*cities[i].red_w);
                            }
                        }
                    }
                }

                if(mi==40){
                    for(int i=1; i<=city_num; i++){
                        if(cities[i].red_w && cities[i].blue_w) {
                            warriors::fight(*cities[i].red_w, *cities[i].blue_w, i);

                            if (cities[i].red_w->died()) {
                                delete cities[i].red_w;
                                cities[i].red_w = nullptr;
                            }
                            if (cities[i].blue_w->died()) {
                                delete cities[i].blue_w;
                                cities[i].blue_w = nullptr;
                            }
                        }
                    }
                }

                if(mi==50){
                    cout << setw(3) << setfill('0') << t << ":50 " << red_quarter.get_hp() << " elements in red headquarter" << endl;
                    cout << setw(3) << setfill('0') << t << ":50 " << blue_quarter.get_hp() << " elements in blue headquarter" << endl;
                }

                if(mi==55){
                    for(int i=0; i<=city_num+1; i++) {
                        if(cities[i].red_w) cities[i].red_w->report();
                        if(cities[i].blue_w) cities[i].blue_w->report();
                    }
                }
            }
            if(!game_over) t++;
        }
    }
    return 0;
}
