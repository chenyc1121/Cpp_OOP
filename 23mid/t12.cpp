#include<bits/stdc++.h>
using namespace std;
map<string, map<string, int> > courseScores;
int main(){
    int n,m;
    cin>>n;
    for(int i=0;i<n;i++){
        string lesson,name;int score;
        cin>>lesson>>name>>score;
        courseScores[lesson][name]=score;
    }
    cin>>m;
    for(int i=0;i<m;i++){
        int k;cin>>k;
        vector<string> les;
        for(int j=0;j<k;j++){
            string s;
            cin>>s;
            les.push_back(s);
        }
        string bestName;
        long long bestScore = -1;
        const auto &firstCourse = courseScores[les[0]];
        for (const auto &studentScore : firstCourse) {
            const string &student = studentScore.first;
            long long total = studentScore.second;
            bool ok = true;
            for (int j = 1; j < k; j++) {
                auto it = courseScores[les[j]].find(student);
                if (it == courseScores[les[j]].end()) {
                    ok = false;
                    break;
                }
                total += it->second;
            }
            if (ok && (total > bestScore || (total == bestScore && student < bestName))) {
                bestScore = total;
                bestName = student;
            }
        }
        cout << bestName << endl;
    }
}