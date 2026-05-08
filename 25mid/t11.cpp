#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Wall {
public:
    map<int, int> intervals;
    int query() {
        int max_len = 0;
        for (const auto& interval : intervals) {
            int len = interval.second - interval.first;
            max_len = max(max_len, len);
        }
        return max_len;
    }
// 在此处补充你的代码
    void bombard(int a, int b) {
        if (a > b) {
            swap(a, b);
        }

        auto it = intervals.lower_bound(a);
        if (it != intervals.begin()) {
            auto prev_it = prev(it);
            if (prev_it->second >= a) {
                it = prev_it;
            }
        }

        while (it != intervals.end() && it->first <= b) {
            a = min(a, it->first);
            b = max(b, it->second);
            it = intervals.erase(it);
        }

        intervals[a] = b;
    }

    void erode() {
        vector<pair<int, int>> saved;
        for (const auto& interval : intervals) {
            saved.push_back(interval);
        }

        intervals.clear();
        for (const auto& interval : saved) {
            bombard(interval.first - 1, interval.second + 1);
        }
    }
};

int main() {
    Wall wall;
    int n;
    cin >> n;
    
    while (n--) {
        int op, a, b;
        cin >> op;
        
        if (op == 1) {
            cin >> a >> b;
            wall.bombard(a, b);
        } else if (op == 2) {
            wall.erode();
        } else if (op == 3) {
            cout << wall.query() << "\n";
        }
    }

    return 0;
}