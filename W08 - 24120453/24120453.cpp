#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) 
        return {};
    int n; file >> n;
    vector<vector<int>> adjList;
    for (int i = 0; i < n; i++) {
        vector<int> neighbors;
        for (int j = 0; j < n; j++) {
            int val; file >> val;
            if (val != 0) neighbors.push_back(j);
        }
        adjList.push_back(neighbors);
    }
    file.close();
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) 
        return {};
    int n; file >> n;
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        int m; file >> m;
        for (int j = 0; j < m; j++) {
            int neighbor; file >> neighbor;
            adjMatrix[i][neighbor] = 1;
        }
    }
    file.close();
    return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) return true;
            return false;
        }
    }
}

int countVertices(const vector<vector<int>>& adjMatrix) 
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int edges = 0, n = adjMatrix.size();
    if (isDirected(adjMatrix)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i][j] != 0)
                    edges++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (adjMatrix[i][j] != 0)
                    edges++;
            }
        }
    }
    return edges;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> isolated;
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        bool hasEdges = false;
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0)
                hasEdges = true;
        }
        if (!hasEdges) isolated.push_back(i);
    }
    return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] != 1)
                return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v = 0; v < n; v++) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = color[u] ^ 1;
                            q.push(v);
                        }
                        else if (color[v] == color[u]) 
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirectedMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] || adjMatrix[j][i])
                undirectedMatrix[i][j] = undirectedMatrix[j][i] = 1;
        }
    }
    return undirectedMatrix;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] == 0)
                complement[i][j] = complement[j][i] = 1;
        }
    }
    return complement;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> temp = adjMatrix;
    stack<int> st;
    vector<int> cycle;
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++)
        {
            degree += temp[i][j];
        }
        if (degree % 2 != 0) 
            return {};
    }
    st.push(0);
    while (!st.empty()) {
        int u = st.top();
        bool found = false;
        for (int v = 0; v < n; v++) {
            if (temp[u][v] > 0) {
                st.push(v);
                temp[u][v]--;
                temp[v][u]--;
                found = true;
                break;
            }
        }
        if (!found) {
            cycle.push_back(u);
            st.pop();
        }
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);
    visited[start] = true;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !visited[v]) {
                spanningTree[u][v] = spanningTree[v][u] = 1;
                visited[v] = true;
                st.push(v);
            }
        }
    }
    return spanningTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !visited[v]) {
                spanningTree[u][v] = spanningTree[v][u] = 1;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return spanningTree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int current = q.front(); q.pop();
        if (current == v) return true;
        for (int neighbor = 0; neighbor < n; neighbor++)
            if (adjMatrix[current][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    vector<bool> visited(n, false);
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
        if (dist[u] == INT_MAX) 
            break;
        visited[u] = true;
        for (int v = 0; v < n; v++)
            if (adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
            }
    }
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path[0] == start ? path : vector<int>();
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v])
                return {};
        }
    }
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) 
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path[0] == start ? path : vector<int>();
}

