/*
    THEORY:
    -------
    LINK STATE ROUTING (DIJKSTRA'S ALGORITHM)
    -----------------------------------------

    Link State routing is used in modern networks (like OSPF).
    Each router:
        • Discovers neighbors and link costs
        • Builds a graph of the whole network
        • Runs DIJKSTRA'S SHORTEST PATH ALGORITHM

    Dijkstra's Algorithm:
        • Start from a source node
        • Mark distances to all nodes (initially infinite)
        • Repeatedly pick the minimum distance unvisited node
        • Update distances of its neighbors
        • Continue until all nodes are visited

    This program:
    -------------
    • Takes number of routers
    • Takes cost matrix between routers
    • Runs Dijkstra from a selected source router
    • Prints shortest path cost to all other routers
*/

#include <iostream>             // For input/output
using namespace std;            // For easy C++ syntax

int main()
{
    int n;                      // Number of nodes (routers)
    int cost[10][10];           // Cost adjacency matrix
    int dist[10];               // Shortest distance from source
    int visited[10];            // Visited array

    cout << "Enter number of nodes: ";
    cin >> n;                   // Read number of routers

    cout << "Enter cost adjacency matrix (999 = no direct path):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];  // Read cost of link i → j
        }
    }

    int src;                   // Source node
    cout << "Enter source node (0 to " << n-1 << "): ";
    cin >> src;

    // Initialize distances and visited status
    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[src][i];   // Initial distances from source
        visited[i] = 0;           // No node visited yet
    }

    visited[src] = 1;             // Mark source node as visited

    // Dijkstra's Algorithm
    for (int k = 1; k < n; k++)
    {
        int min = 999;            // Large value for comparison
        int u = 0;                // Node with minimum distance

        // Find unvisited node with smallest distance
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 0 && dist[i] < min)
            {
                min = dist[i];
                u = i;            // This is the next node to explore
            }
        }

        visited[u] = 1;           // Mark this node as visited

        // Update distances of neighbors of 'u'
        for (int v = 0; v < n; v++)
        {
            if (visited[v] == 0 && dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];   // Update shortest path
            }
        }
    }

    // Print shortest distances
    cout << "\nShortest distances from node " << src << ":\n";
    for (int i = 0; i < n; i++)
    {
        cout << "To node " << i << ": " << dist[i] << endl;
    }

    return 0;   // End of program
}


/*
    ===================================
    SAMPLE INPUT / OUTPUT (AS COMMENTS)
    ===================================

    INPUT:
    Enter number of nodes: 4
    Enter cost adjacency matrix (999 = no direct path):
    0   1   4   999
    1   0   2   6
    4   2   0   3
    999 6   3   0
    Enter source node (0 to 3): 0

    OUTPUT:
    Shortest distances from node 0:
    To node 0: 0
    To node 1: 1
    To node 2: 3
    To node 3: 6
*/
