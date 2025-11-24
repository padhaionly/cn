/*
    THEORY:
    -------
    DISTANCE VECTOR ROUTING ALGORITHM
    ---------------------------------
    This is a dynamic routing algorithm used in networks.
    Every router maintains a table (distance vector) containing:

        • Destination router
        • Distance (cost) to reach destination

    Routers periodically exchange their tables with neighbors and update costs.

    Bellman–Ford Update Rule:
        Distance to destination = 
            cost(neighbor) + neighbor's distance to destination

    This program:
    -------------
    • Accepts number of nodes
    • Accepts cost matrix between nodes
    • Applies Distance Vector routing
    • Prints shortest path cost table
*/

#include <iostream>      // For input/output
using namespace std;     // Avoid std:: prefix everywhere

int main()
{
    int n;               // Number of nodes
    int cost[10][10];    // Cost adjacency matrix
    int dist[10][10];    // Distance vector table

    cout << "Enter number of nodes: ";
    cin >> n;            // Read total nodes

    // Read cost matrix
    cout << "Enter cost adjacency matrix (0 for self, 999 for no link):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];      // Read cost of i → j
            dist[i][j] = cost[i][j]; // Initialize distance table
        }
    }

    // Apply Distance Vector (Bellman-Ford)
    for (int k = 0; k < n; k++)           // Relax edges n times
    {
        for (int i = 0; i < n; i++)       // For each source
        {
            for (int j = 0; j < n; j++)   // For each destination
            {
                // Check if going through K improves the path i → j
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];  // Update shortest path
                }
            }
        }
    }

    // Print final distance vector table
    cout << "\nFinal Distance Vector Table:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << dist[i][j] << "\t";   // Print distance i → j
        }
        cout << endl;
    }

    return 0;    // End of program
}


/*
    ===================================
    SAMPLE INPUT / OUTPUT (AS COMMENTS)
    ===================================

    INPUT:
    Enter number of nodes: 3
    Enter cost adjacency matrix (0 for self, 999 for no link):
    0   2   7
    2   0   1
    7   1   0

    OUTPUT:
    Final Distance Vector Table:
    0   2   3
    2   0   1
    3   1   0
*/
