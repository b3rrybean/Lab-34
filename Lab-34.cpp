#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for pair<int,int>

class Graph {
public:
    // A vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    vector<string> locations = {
        "My House",
        "Coffee Shop",
        "Park",
        "Library",
        "Grocery Store",
        "School",
        "Community Center",
        "Dog Park",
        "Playground"
    };

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // Resize the vector to hold SIZE elements
        adjList.resize(SIZE);

        // Add edges to the graph (undirected)
        for (auto &edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int w = edge.weight;

            adjList[u].push_back(make_pair(v, w));
            adjList[v].push_back(make_pair(u, w)); // undirected
        }
    }

    void printNeighborhood() {
        cout << "\nNeighborhood Walking Map\n";
        cout << "==========================\n";

        for (int i = 0; i < SIZE; i++) {
            cout << locations[i] << " connects to:\n";
            for (Pair p : adjList[i]) {
                cout << "  → " << locations[p.first]
                     << " (Walking time: " << p.second << " mins)\n";
            }
            cout << endl;
        }
    }

    // DFS helper (recursive)
    void DFSUtil(int u, vector<bool> &visited) {
        visited[u] = true;
        cout << "Inspecting " << locations[u] << endl;

        for (Pair p : adjList[u]) {
            if (!visited[p.first]) {
                DFSUtil(p.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "\nDFS Route Inspection (deep exploration)\n";
        cout << "Starting from " << locations[start] << endl;
        cout << "====================================\n";

        DFSUtil(start, visited);
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Neighborhood Spread (layer-by-layer)\n";
        cout << "Starting from " << locations[start] << endl;
        cout << "====================================\n";

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            cout << "Reached " << locations[u] << endl;

            for (Pair p : adjList[u]) {
                if (!visited[p.first]) {
                    visited[p.first] = true;
                    q.push(p.first);
                }
            }
        }
    }

    // ---------- SHORTEST PATH (DIJKSTRA) ----------
    void shortestPath(int start) {
        vector<int> distance(SIZE, INT_MAX);
        distance[start] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int currentNode = pq.top().second;
            pq.pop();

            for (Pair neighbor : adjList[currentNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (distance[currentNode] + weight < distance[nextNode]) {
                    distance[nextNode] = distance[currentNode] + weight;
                    pq.push({distance[nextNode], nextNode});
                }
            }
        }

        cout << "\nShortest path from node " << start 
             << " (" << locations[start] << "):\n";

        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : " << distance[i]
                 << " mins (" << locations[i] << ")\n";
        }
    }

    // ---------- MINIMUM SPANNING TREE (PRIM'S) ----------
    void minimumSpanningTree() {
        vector<bool> inMST(SIZE, false);
        vector<int> key(SIZE, INT_MAX);
        vector<int> parent(SIZE, -1);

        key[0] = 0;  // Start from node 0 (My House)

        for (int count = 0; count < SIZE - 1; count++) {
            int minKey = INT_MAX;
            int u = -1;

            // Find vertex with minimum key not yet included
            for (int v = 0; v < SIZE; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            inMST[u] = true;

            for (Pair neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        cout << "\nMinimum Spanning Tree edges:\n";
        cout << "====================================\n";

        for (int i = 1; i < SIZE; i++) {
            cout << "Edge from " << locations[parent[i]]
                 << " to " << locations[i]
                 << " with walking time: " << key[i] << " mins\n";
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) → edge from x to y with weight w
        {0,1,8},  {0,2,21},
        {1,2,6},  {1,3,5},  {1,4,4},
        {2,7,11}, {2,8,8},
        {3,4,9},
        {5,6,10}, {5,7,15}, {5,8,5},
        {6,7,3},  {6,8,7}
    };

    // Create graph
    Graph neighborhood(edges);

    // Print adjacency list representation of graph
    neighborhood.printNeighborhood();
    neighborhood.DFS(0);
    neighborhood.BFS(0);
    neighborhood.shortestPath(0);
    neighborhood.minimumSpanningTree();

    return 0;
}
