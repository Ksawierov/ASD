#include <bits/stdc++.h>
using namespace std;

constexpr long long MOD = 1e9 + 7;

int main() {
    int n;
    long long wynik = 0;
    cin >> n;
    int t[n];

    for (int i = 0; i < n; i++)
        cin >> t[i];
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            wynik += (long long)(pow((long long)(t[j] - t[i]), 2)) % MOD;
        }
    }
    cout << wynik % MOD << '\n';
}