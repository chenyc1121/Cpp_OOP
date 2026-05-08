#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin>>n;
    map<int, list<int>> lists;
    
    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd == "new") {
            int id;
            cin >> id;
            lists[id] = list<int>();
        } else if (cmd == "add") {
            int id, num;
            cin >> id;
            cin >> num;
            lists[id].push_back(num);
            lists[id].sort(); 
        } else if (cmd == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            if (id1 != id2) {
                lists[id1].merge(lists[id2]);
            }
        } else if (cmd == "unique") {
            int id;
            cin >> id;
            lists[id].unique();
        } else if (cmd == "out") {
            int id;
            cin >> id;
            bool first = true;
            for (int val : lists[id]) {
                if (!first) cout << " ";
                cout << val;
                first = false;
            }
            cout << endl;
        }
    }
    
    return 0;
}