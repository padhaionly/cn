#include <iostream>
using namespace std;

const int INF = 1000000000; // Infinity

// Print routing table
void printTable(int dist[], int n, int src) {
    cout << "Routing Table for Node " << src << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] >= INF) cout << "Node " << i << ": INF\n";
        else cout << "Node " << i << ": " << dist[i] << "\n";
    }
    cout << endl;
}

// ----------------- Distance Vector Routing (DVR) -----------------
void distanceVectorRouting(int cost[][10], int n) {
    int dist[10][10];

    // Copy original cost matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = cost[i][j];

    bool changed = true;

    cout << "\n===== Distance Vector Routing (DVR) =====\n";

    while (changed) {
        changed = false;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        int newDist = dist[i][k] + dist[k][j];
                        if (newDist < dist[i][j]) {
                            dist[i][j] = newDist;
                            changed = true;
                        }
                    }
                }
            }
        }
    }

    cout << "DVR Converged.\n\n";

    for (int i = 0; i < n; i++)
        printTable(dist[i], n, i);
}

// ---------------------- Dijkstra Algorithm ----------------------
void dijkstra(int graph[][10], int n, int src, int dist[]) {
    bool visited[10] = {false};

    for (int i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;

        // Pick smallest unvisited distance node
        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] < INF) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v])
                    dist[v] = newDist;
            }
        }
    }
}

// ------------------- Link State Routing (LSR) -------------------
void linkStateRouting(int cost[][10], int n) {
    cout << "\n===== Link State Routing (LSR) =====\n";

    int dist[10];

    for (int src = 0; src < n; src++) {
        dijkstra(cost, n, src, dist);
        printTable(dist, n, src);
    }
}

// ----------------------------- MAIN -----------------------------
int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    int cost[10][10];

    cout << "Enter cost adjacency matrix (use 999 for no link):\n";

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i == j) cost[i][j] = 0;
            if (cost[i][j] < 0) cost[i][j] = INF;
        }

    distanceVectorRouting(cost, n);
    linkStateRouting(cost, n);

    return 0;
}




// sample input :
// 4
// 0 5 999 10
// 5 0 3 999
// 999 3 0 1
// 10 999 1 0

