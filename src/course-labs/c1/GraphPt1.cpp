#include <iostream>
#include "GraphOne.h"

int main()
{
    // Create a graph of strings
    Graph<std::string> g;

    // Add vertices and edges
    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 2);
    g.addEdge("B", "C", 5);
    g.addEdge("B", "D", 10);
    g.addEdge("C", "D", 3);
    g.addEdge("C", "E", 4);
    g.addEdge("D", "E", 1);

    std::vector<std::tuple<std::string, std::string, int>> mst;
    int totalCost = 0;

    // Call Prim's algorithm
    g.prims(mst, totalCost);

    // Output the MST and its total cost
    std::cout << "Minimum Spanning Tree (Prim's):\n";
    for (const auto& [from, to, weight] : mst)
    {
        std::cout << from << " - " << to << " (weight: " << weight << ")\n";
    }

    std::cout << "Total cost: " << totalCost << std::endl;

    return 0;
}
