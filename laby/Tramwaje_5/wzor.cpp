#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 1e15;

struct Edge {
    int end;
    int period;
    int cost;
};

struct Node {
    int num;
    long long cost;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.cost > b.cost;
    }
};

long long f(long long arrTime, long long period) {
    if(arrTime == 0) 
        return 0;
    return (((arrTime - 1) / period) + 1 ) * period;
}

vector<long long> dijkstra(const vector<vector<Edge>>& G) {
    int n = G.size();
    vector<long long> dist(n, INF);
    vector<bool> vis(n, 0);
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({1, 0});
    dist[1] = 0;

    Node node;
    while(!pq.empty()) {
        node = pq.top();
        pq.pop();
        if(dist[node.num] < node.cost)
            continue;
        vis[node.num] = true;
    
        // cout << node.num << " " << node.cost << "\n";
        for (const auto& s : G[node.num]) {
            long long min_cost = min(dist[s.end], f(dist[node.num], s.period) + s.cost);
            if(min_cost < dist[s.end]) {
                pq.push({s.end, min_cost});
                dist[s.end] = min_cost;
            }
        }
    }
    vector<long long> res(n);
    for(int i = 1; i < n; i++) {
        dist[i] == INF ? res[i] = -1 : res[i] = dist[i];
    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int a, b, p, cost; // p - period
    // cout << INF << '\n';
    vector<vector<Edge>> G(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> p >> cost;
        G[a].push_back({b, p, cost});
    }
    vector<long long> v = dijkstra(G);
    for (int i = 1; i <= n; i++) {
        cout << v[i] << '\n';
    }
}