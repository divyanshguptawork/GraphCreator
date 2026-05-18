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
};
