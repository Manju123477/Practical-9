#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Alias to make the code cleaner. 
// For the adjacency list, it stores {neighbor_vertex, edge_weight}.
// For the priority queue, it stores {edge_weight, vertex_to_reach}.
typedef pair<int, int> pii;

void primMST(int V, vector<vector<pii>>& adj) {
    // Min-heap priority queue to pick the minimum weight edge efficiently
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    int src = 0; // Start the spanning tree from vertex 0

    // key[] tracks the minimum weight to reach a vertex
    // parent[] stores the constructed MST
    // inMST[] tracks vertices already included in the MST
    vector<int> key(V, 1e9); 
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    // Initialize the source vertex
    pq.push({0, src});
    key[src] = 0;

    while (!pq.empty()) {
        // Extract the vertex with the minimum key value
        int u = pq.top().second;
        pq.pop();

        // If the vertex is already in the MST, ignore it (lazy deletion)
        if (inMST[u]) continue;

        // Mark the picked vertex as included in the MST
        inMST[u] = true;

        // Iterate through all adjacent vertices of the picked vertex
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // If v is not in MST and the edge weight is smaller than its current key
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    // Print the constructed Minimum Spanning Tree
    cout << "Edge \tWeight\n";
    int totalWeight = 0;
    
    // We start from 1 because vertex 0 is the root/source and has no parent
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

    // Helper lambda function to add undirected edges
    auto addEdge = [&](int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    };

    // Creating the graph based on the vertices and edge weights
    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    // Execute Prim's Algorithm
    primMST(V, adj);

    return 0;
}
