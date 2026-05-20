#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX = 20;
const int INF = 999999; // Represents no connection

struct Graph {
    string vertices[MAX];
    int adjMatrix[MAX][MAX];
    int vertexCount = 0;

    Graph() {
        // Initialize matrix with INF (no edges)
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                adjMatrix[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    // Find index of a label
    int getIndex(string label) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == label) return i;
        }
        return -1;
    }

    void addVertex(string label) {
        if (vertexCount < MAX) {
            vertices[vertexCount++] = label;
        } else {
            cout << "Graph full (Max 20 vertices)." << endl;
        }
    }

    // Add a directed, weighted edge from 'start' vertex to 'end' vertex
    void addEdge(string start, string end, int weight) {
        int u = getIndex(start);
        int v = getIndex(end);
        if (u != -1 && v != -1) {
            adjMatrix[u][v] = weight;
        } else {
            cout << "Vertex not found." << endl;
        }
    }

    // Remove an edge by resetting its matrix cell back to INF
    void removeEdge(string start, string end) {
        int u = getIndex(start);
        int v = getIndex(end);
        if (u != -1 && v != -1) {
            adjMatrix[u][v] = INF;
        }
    }

    // Print out the adjacency table formatting for debugging
    void printTable() {
        cout << "\nAdjacency Table:\n" << setw(6) << " ";
        for (int i = 0; i < vertexCount; i++) cout << setw(6) << vertices[i];
        cout << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(6) << vertices[i];
            for (int j = 0; j < vertexCount; j++) {
                if (adjMatrix[i][j] == INF) cout << setw(6) << "INF";
                else cout << setw(6) << adjMatrix[i][j];
            }
            cout << endl;
        }
    }
};

