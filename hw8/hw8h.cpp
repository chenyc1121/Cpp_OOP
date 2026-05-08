#include<bits/stdc++.h>
using namespace std;

// 计算不同质因数的个数
int get_value(int n) {
    int count = 0;
    int temp = n;
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            count++;
            while (temp % i == 0) temp /= i;
        }
    }
    if (temp > 1) {
        if(temp!=n)count++;
    }
    return count;
}

struct Node {
    int val;
    int cnt;
    // 优先级比较逻辑
    bool operator<(const Node& b) const {
        if (cnt != b.cnt) return cnt < b.cnt; // 数量多者优先
        return val < b.val;                   // 数值大者优先
    }
};

int main() {
    int num;
    cin >> num;
    multiset<Node> s; // 使用 multiset 处理可能的重复数字

    while (num--) {
        for (int i = 0; i < 10; i++) {
            int n;
            cin >> n;
            s.insert({n, get_value(n)});
        }
        
        // 最高优先级在最后，最低优先级在最前
        auto highest = *s.rbegin();
        auto lowest = *s.begin();
        
        cout << highest.val << " " << lowest.val << endl;
        
        // 删除对应的迭代器（只删一个，防止删掉所有同值的元素）
        s.erase(prev(s.end()));
        s.erase(s.begin());
    }
    return 0;
}