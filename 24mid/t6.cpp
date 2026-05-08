#include<iostream>
using namespace std;
int exchangeBits(unsigned int n) {
    return ((n&0x55555555)<<1)|((n&0xaaaaaaaa)>>1);
// 在此处补充你的代码
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        unsigned x;
        cin >> x;
        cout << exchangeBits(x) << endl;
    }
    return 0;
}