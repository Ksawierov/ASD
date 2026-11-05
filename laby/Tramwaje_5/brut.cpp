#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 1e15;

struct Edge {
    int dest;
    int per;    // Period
    int dur;    // Duration
};

long long countDist(long long curTime, Edge edge) {
    if(curTime == 0)
        return edge.dur;
    return ((curTime - 1) / edge.per + 1) * edge.per + edge.dur;
}

void DFS(int w, const vector<vector<Edge>> &G, vector<long long> &dist, vector<bool> &vis) {
    vis[w] = true;
    for (auto v : G[w]) {
        long long new_dist = countDist(dist[w], v);
        if (new_dist < dist[v.dest]) {
            dist[v.dest] = new_dist;
            DFS(v.dest, G, dist, vis);
            // cout << w << " " << v.dest << " " << dist[v.dest] << '\n';
        }
    }
}

vector<long long> solve(vector<vector<Edge>> G) {
    int n = G.size() - 1;
    vector<long long> dist(n + 1, INF);
    vector<bool> vis(n + 1, false); // Here we mark visited nodes
    dist[1] = 0;
    for(int i = 1; i < n; i++) {
        if (!vis[i]) {
            DFS(i, G, dist, vis);
        }
    }
    return dist;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> G(n + 1);
    Edge edge;
    int start;
    for (int i = 0; i < m; i++) {
        cin >> start >> edge.dest >> edge.per >> edge.dur;
        G[start].push_back(edge);
    }
    vector<long long> results = solve(G);
    // cout << results.size() << "\n";
    for (int i = 1; i < (int)results.size(); i++)  {
        results[i] == INF ? results[i] = -1 : results[i] = results[i];
        cout << results[i] << '\n';
    }

    return 0;
}