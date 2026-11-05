#include <bits/stdc++.h>
using namespace std;

struct result {
    int car_num;
    int max_time;
};

struct car {
    int arr;
    int dep;
};

result solve(int n, int maxval, vector<car> v) {
    result res = {0, 0};
    vector<int> pref(maxval + 1, 0);

    for (int i = 0; i < n; i++) {
        pref[v[i].arr]++;
        pref[v[i].dep]--;
    }

    for (int i = 0; i <= maxval; i++) {
        if(i > 0) 
            pref[i] += pref[i - 1];
        if(res.car_num < pref[i]) {
            res.car_num = pref[i];
            res.max_time = i;
        }
    }
    return res;
}

int main() {
    int n, arr, dep, maxval = 0;
    cin >> n;
    vector<car> v;

    for (int i = 0; i < n; i++) { 
        cin >> arr >> dep;
        maxval = max(maxval, max(arr, dep));
        v.push_back({arr, dep});
    }
    result res = solve(n, maxval, v);
    
    cout << res.car_num << " " << res.max_time << '\n';

}