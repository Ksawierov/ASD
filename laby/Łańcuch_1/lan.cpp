#include <iostream>
using namespace std;

constexpr long long MOD = 1e9 + 7;

long long mod(long long val) {
    return ((val % MOD) + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    
    long long el;
    long long suma_kw = 0; // sum((a_i)^2)
    long long suma = 0; // sum(a_i)

    for(int i = 0; i < n; i++) {
        cin >> el;
        suma_kw = mod(suma_kw + mod(el * el));
        suma = mod(suma + el);
    }

    // Wzorek: n * sum((a_i)^2) - (sum(a_i))^2
    long long w1 = mod(suma_kw * n);
    long long w2 = mod(suma * suma);
    long long wynik = mod(w1 - w2);

    cout << wynik << '\n';

    return 0;
}