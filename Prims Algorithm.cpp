#include <iostream>
#include <vector>
#include <queue>

using namespace std;


typedef pair<int, int> pii;

void primMST(int V, vector<vector<pii>>& adj) {
    
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    int src = 0; 

    
    vector<int> key(V, 1e9); 
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    
    pq.push({0, src});
    key[src] = 0;

    while (!pq.empty()) {
        
        int u = pq.top().second;
        pq.pop();

        
        if (inMST[u]) continue;

        
        inMST[u] = true;

        
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    
    cout << "Edge \tWeight\n";
    int totalWeight = 0;
    
    
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " \t" << key[i] << "\n";
            totalWeight += key[i];
        }
    }
    cout << "---------------------\n";
    cout << "Total MST Weight: " << totalWeight << "\n";
}

int main() {
    int V = 5;
    vector<vector<pii>> adj(V);

   
    auto addEdge = [&](int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    };

    
    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    
    primMST(V, adj);

    return 0;
}
