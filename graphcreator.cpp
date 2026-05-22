#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Maximum number of vertices allowed in the adjacency table
const int MAX = 20;
// Representation of infinity for vertices that share no connected edge
const int INF = 999999; 

struct Graph {
    string vertices[MAX];
    int adjMatrix[MAX][MAX];
    int vertexCount = 0;

    Graph() {
        // Initialize matrix: 0 weight to self, INF (infinity) for everything else
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                adjMatrix[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    // Helper function to find the array index matching a string label
    int getIndex(string label) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == label) return i;
        }
        return -1;
    }

    // Adds a unique vertex label to our tracked list
    void addVertex(string label) {
        if (getIndex(label) != -1) {
            cout << "Vertex '" << label << "' already exists." << endl;
            return;
        }
        if (vertexCount < MAX) {
            vertices[vertexCount++] = label;
        } else {
            cout << "Graph full (Max 20 vertices reached)." << endl;
        }
    }

    // Adds a directed, positively weighted edge between two existing vertices
    void addEdge(string start, string end, int weight) {
        int u = getIndex(start);
        int v = getIndex(end);
        if (u != -1 && v != -1) {
            if (weight < 0) {
                cout << "Edge weight must be a positive integer." << endl;
                return;
            }
            adjMatrix[u][v] = weight;
        } else {
            cout << "One or both vertices not found." << endl;
        }
    }

    // Disconnects a directed edge by restoring its intersection to INF
    void removeEdge(string start, string end) {
        int u = getIndex(start);
        int v = getIndex(end);
        if (u != -1 && v != -1) {
            adjMatrix[u][v] = INF;
        } else {
            cout << "Edge vertices not found." << endl;
        }
    }

    // Removes a vertex completely, shifting rows/columns to clean the matrix grid
    void removeVertex(string label) {
        int index = getIndex(label);
        if (index == -1) {
            cout << "Vertex not found." << endl;
            return;
        }

        // Shift label array elements left over the deleted index
        for (int i = index; i < vertexCount - 1; i++) {
            vertices[i] = vertices[i + 1];
        }

        // Shift rows up in the adjacency matrix grid
        for (int i = index; i < vertexCount - 1; i++) {
            for (int j = 0; j < vertexCount; j++) {
                adjMatrix[i][j] = adjMatrix[i + 1][j];
            }
        }

        // Shift columns left in the adjacency matrix grid
        for (int j = index; j < vertexCount - 1; j++) {
            for (int i = 0; i < vertexCount; i++) {
                adjMatrix[i][j] = adjMatrix[i][j + 1];
            }
        }

        vertexCount--;
    }

    // Prints out a beautifully formatted layout of the graph structure
    void printTable() {
        if (vertexCount == 0) {
            cout << "\nThe graph is empty." << endl;
            return;
        }
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

    // Finds the shortest path mapping using Dijkstra's algorithm
    void findShortestPath(string startLabel, string endLabel) {
        int start = getIndex(startLabel);
        int target = getIndex(endLabel);
        if (start == -1 || target == -1) {
            cout << "Start or Target vertex does not exist." << endl;
            return;
        }

        int dist[MAX];
        int parent[MAX];
        bool visited[MAX] = {false};

        // Initialize helper distances to infinity
        for (int i = 0; i < vertexCount; i++) {
            dist[i] = INF;
            parent[i] = -1;
        }
        dist[start] = 0;

        // Loop across vertices evaluating minimum path variations
        for (int count = 0; count < vertexCount - 1; count++) {
            int minDist = INF, u = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && dist[v] <= minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }

            if (u == -1 || dist[u] == INF) break;
            visited[u] = true;

            // Update edge lengths for neighboring nodes
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print final processing output summary
        if (dist[target] == INF) {
            cout << "No path exists between " << startLabel << " and " << endLabel << endl;
        } else {
            cout << "Shortest path total weight: " << dist[target] << endl;
            cout << "Path: ";
            vector<string> path;
            for (int curr = target; curr != -1; curr = parent[curr]) {
                path.insert(path.begin(), vertices[curr]);
            }
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    int choice;
    string s1, s2;
    int w;

    while (true) {
        cout << "\nGRAPH MENU" << endl;
        cout << "1. Add Vertex\n2. Add Edge\n3. Remove Vertex\n4. Remove Edge\n5. Print Adjacency Table\n6. Find Shortest Path (Dijkstra)\n7. Exit" << endl;
        cout << "Choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid numeric option." << endl;
            continue;
        }

        if (choice == 1) {
            cout << "Enter unique label for vertex: "; cin >> s1;
            g.addVertex(s1);
        } else if (choice == 2) {
            cout << "Enter starting vertex, ending vertex, and path weight: "; cin >> s1 >> s2 >> w;
            g.addEdge(s1, s2, w);
        } else if (choice == 3) {
            cout << "Enter vertex label to completely remove: "; cin >> s1;
            g.removeVertex(s1);
        } else if (choice == 4) {
            cout << "Enter edge start and edge end to sever: "; cin >> s1 >> s2;
            g.removeEdge(s1, s2);
        } else if (choice == 5) {
            g.printTable();
        } else if (choice == 6) {
            cout << "Enter starting destination and target endpoint: "; cin >> s1 >> s2;
            g.findShortestPath(s1, s2);
        } else if (choice == 7) {
            cout << "Exiting system application." << endl;
            break;
        } else {
            cout << "Invalid menu item selected. Try again." << endl;
        }
    }
    return 0;
}
