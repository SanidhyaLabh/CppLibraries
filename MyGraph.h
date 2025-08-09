#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <climits>
#include <tuple>
#include <iomanip>

class Graph {
    int vertices;
    bool directed;
    std::vector<std::vector<std::pair<int,int>>> adjList;
    std::vector<std::tuple<int,int,int>> edges; // u,v,w

public:
    Graph(int v = 0, bool dir = false) {
        vertices = v;
        directed = dir;
        adjList.resize(vertices);
    }

    void addVertex() {
        vertices++;
        adjList.resize(vertices);
    }

    void removeVertex(int v) {
        if (v < 0 || v >= vertices) return;
        adjList.erase(adjList.begin() + v);
        for (size_t i = 0; i < adjList.size(); i++) {
            adjList[i].erase(
                std::remove_if(adjList[i].begin(), adjList[i].end(),
                               [v](std::pair<int,int> p){ return p.first == v; }),
                adjList[i].end()
            );
            for (size_t j = 0; j < adjList[i].size(); j++) {
                if (adjList[i][j].first > v) adjList[i][j].first--;
            }
        }
        vertices--;
    }

    void addEdge(int u, int v, int w = 1) {
        if (u >= vertices || v >= vertices || u < 0 || v < 0) return;
        adjList[u].push_back(std::make_pair(v, w));
        edges.push_back(std::make_tuple(u, v, w));
        if (!directed) {
            adjList[v].push_back(std::make_pair(u, w));
            edges.push_back(std::make_tuple(v, u, w));
        }
    }

    void removeEdge(int u, int v) {
        if (u >= vertices || v >= vertices) return;
        adjList[u].erase(
            std::remove_if(adjList[u].begin(), adjList[u].end(),
                           [v](std::pair<int,int> p){ return p.first == v; }),
            adjList[u].end()
        );
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                           [u,v](std::tuple<int,int,int> t){ return std::get<0>(t) == u && std::get<1>(t) == v; }),
            edges.end()
        );
        if (!directed) {
            adjList[v].erase(
                std::remove_if(adjList[v].begin(), adjList[v].end(),
                               [u](std::pair<int,int> p){ return p.first == u; }),
                adjList[v].end()
            );
        }
    }

    void clear() {
        adjList.clear();
        edges.clear();
        vertices = 0;
    }

    void printAdjList() {
        for (int i = 0; i < vertices; i++) {
            std::cout << i << ": ";
            for (size_t j = 0; j < adjList[i].size(); j++) {
                std::cout << "(" << adjList[i][j].first << "," << adjList[i][j].second << ") ";
            }
            std::cout << "\n";
        }
    }

    void printAdjMatrix() {
        std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices, 0));
        for (int i = 0; i < vertices; i++) {
            for (size_t j = 0; j < adjList[i].size(); j++) {
                matrix[i][adjList[i][j].first] = adjList[i][j].second;
            }
        }
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void BFS(int start) {
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            std::cout << node << " ";
            for (size_t i = 0; i < adjList[node].size(); i++) {
                int neighbor = adjList[node][i].first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << "\n";
    }

    void DFSUtil(int v, std::vector<bool> &visited) {
        visited[v] = true;
        std::cout << v << " ";
        for (size_t i = 0; i < adjList[v].size(); i++) {
            int neighbor = adjList[v][i].first;
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        std::vector<bool> visited(vertices, false);
        DFSUtil(start, visited);
        std::cout << "\n";
    }

    void Dijkstra(int src) {
        std::vector<int> dist(vertices, INT_MAX);
        dist[src] = 0;
        typedef std::pair<int,int> pii;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.push(std::make_pair(0, src));

        while (!pq.empty()) {
            pii top = pq.top();
            pq.pop();
            int d = top.first;
            int u = top.second;
            if (d > dist[u]) continue;
            for (size_t i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i].first;
                int w = adjList[u][i].second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }

        for (int i = 0; i < vertices; i++) {
            std::cout << "Distance from " << src << " to " << i << " = " << dist[i] << "\n";
        }
    }

    void BellmanFord(int src) {
        std::vector<int> dist(vertices, INT_MAX);
        dist[src] = 0;
        for (int i = 1; i <= vertices-1; i++) {
            for (size_t j = 0; j < edges.size(); j++) {
                int u = std::get<0>(edges[j]);
                int v = std::get<1>(edges[j]);
                int w = std::get<2>(edges[j]);
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        for (size_t j = 0; j < edges.size(); j++) {
            int u = std::get<0>(edges[j]);
            int v = std::get<1>(edges[j]);
            int w = std::get<2>(edges[j]);
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                std::cout << "Negative weight cycle detected\n";
                return;
            }
        }
        for (int i = 0; i < vertices; i++) {
            std::cout << "Distance from " << src << " to " << i << " = " << dist[i] << "\n";
        }
    }

    void FloydWarshall() {
        std::vector<std::vector<int>> dist(vertices, std::vector<int>(vertices, INT_MAX));
        for (int i = 0; i < vertices; i++) dist[i][i] = 0;
        for (int u = 0; u < vertices; u++) {
            for (size_t i = 0; i < adjList[u].size(); i++) {
                int v = adjList[u][i].first;
                dist[u][v] = adjList[u][i].second;
            }
        }
        for (int k = 0; k < vertices; k++) {
            for (int i = 0; i < vertices; i++) {
                for (int j = 0; j < vertices; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][j] == INT_MAX) std::cout << "INF ";
                else std::cout << dist[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void plotEquation(double (*func)(double), double xMin, double xMax, double yMin, double yMax, int width = 80, int height = 20) {
        std::vector<std::string> canvas(height, std::string(width, ' '));
        for (int i = 0; i < width; i++) {
            double x = xMin + (xMax - xMin) * i / (width - 1);
            double y = func(x);
            int j = (int)((yMax - y) * (height - 1) / (yMax - yMin));
            if (j >= 0 && j < height) {
                canvas[j][i] = '*';
            }
        }
        for (int j = 0; j < height; j++) {
            std::cout << canvas[j] << "\n";
        }
    }
};

#endif
