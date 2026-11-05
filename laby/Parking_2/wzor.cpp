#include <bits/stdc++.h>
using namespace std;

enum EventType {
    DEPARTURE = 0,  // Smaller value guarantees, 
                    // departures are processed before arrivals
    ARRIVAL = 1
};

struct Event{
    int timestamp; 
    EventType type;
};

struct Result {
    int car_num;
    int best_time;
};

// We order by the action time and then by type of action, first we remove 
// departing cars and then accept arriving cars. So we can avoid incorrect
// score of too much cars at the parking
bool comp(const Event& el1, const Event& el2) {
    if(el1.timestamp == el2.timestamp) 
        return el1.type < el2.type;
    return el1.timestamp < el2.timestamp;
}


Result solve (vector<Event>& v) {

    Result res = {0, 0};

    sort(v.begin(), v.end(), comp);

    int ctr = 0;
    for (const auto& event : v) {
        if(!event.type) 
            ctr--;
        else 
            ctr++; 

        if(ctr > res.car_num) {
            res.car_num = ctr;
            res.best_time = event.timestamp;
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, arr, dep;
    cin >> n;
    vector<Event> v;
    v.reserve(n * 2);

    for (int i = 0; i < n; i++) { 
        cin >> arr >> dep;
        v.push_back({arr, ARRIVAL});
        v.push_back({dep, DEPARTURE});
    }
    Result res = solve(v);
    
    cout << res.car_num << " " << res.best_time << '\n';
}