#include <iostream>
#include <vector>
#include <queue>
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
        cout << "\nNeighborhod Walking Map\n";
        cout << "==========================\n";

        for (int i = 0, i < SIZE; i++) {
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
        cout << "n\nDFS Route Inspection (deep exploration)\n";
        cout << "Starting from " << locations[start] << endl;
        cout << "====================================\n";

        DFSUtil(start, visited);
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (Pair p : adjList[u]) {
                int v = p.first;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
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
    Graph graph(edges);

    // Print adjacency list representation of graph
    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
