#include <bits/stdc++.h>
using namespace std;

priority_queue<int> pqMax, pqMin;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        if (!pqMax.empty() && !pqMin.empty()) {
            if (-pqMin.top() > val) {
                pqMax.push(val);
            }
            else {
                pqMin.push(-val);
            }
            if (pqMax.size() < pqMin.size()) {
                pqMax.push(-pqMin.top());
                pqMin.pop();
            }
        } 
        else {
            pqMax.push(val);
        }
        if(pqMax.size() > pqMin.size() + 1) {
            pqMin.push(-pqMax.top());
            pqMax.pop();
        }
       cout << pqMax.top() << '\n';
    }
}