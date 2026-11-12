#include <bits/stdc++.h>
using namespace std;



int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
        vector<int> p(i + 1);
        for(int j = 0; j < i + 1; j++) {
            p[j] = v[j];
        }
        sort(p.begin(), p.end());
        cout << p[i / 2] << '\n';
    }
}