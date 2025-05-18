#ifndef GRAPH_H
#define GRAPH_H
#include <utility>
#include <vector>
#include <climits>
#include <tuple>
#include <string>
#include <unordered_set>

const int INFINIT_COST = INT_MAX;

template <class T>
class Graph
{
private:
	std::unordered_map<T, std::vector<std::pair<T, int>>> adjList;
    int edgeCount;
	
public:
	Graph();
	virtual ~Graph() = default;
	Graph(const Graph& other) = delete;
	Graph& operator=(const Graph& other) = delete;
	void addVertex(T theNode);
	void addEdge(T from, T to, int weight = 0);
	std::vector<T> getAllNeighboursTo(T vertex);
	int getNrOfVertices() const;
	int getNrOfEdges() const;
	void kruskals(std::vector<std::tuple<T, T, int>>& mst, int &totalCost);
	void prims(std::vector<std::tuple<T, T, int>>& mst, int &totalCost);
	void readFromFile(std::string file);

	std::string depthFirstSearch(T from);
	std::string breadthFirstSearch(T from);
};


#endif

template<class T>
Graph<T>::Graph() : edgeCount(0)
{
}

template<class T>
void Graph<T>::addVertex(T theNode)
{
    if (adjList.find(theNode) == adjList.end()) {
        adjList[theNode] = {};
    }
}

template<class T>
void Graph<T>::addEdge(T from, T to, int weight)
{
    addVertex(from);
    addVertex(to);
    adjList[from].push_back({to, weight});
    adjList[to].push_back({from, weight});
    edgeCount+=2;
}

template<class T>
std::vector<T> Graph<T>::getAllNeighboursTo(T vertex)
{
	std::vector<T> neighbours;
    for (const auto& pair : adjList[vertex]) {
        neighbours.push_back(pair.first);
    }

    std::sort(neighbours.begin(), neighbours.end());  // Alphabetical order
    return neighbours;
}

template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>> &mst, int& totalCost)
{
    mst.clear();
    totalCost = 0;

    // 1. Samla alla kanter (undvik duplicerade för oriktad graf)
    std::vector<std::tuple<int, T, T>> edges; // (weight, u, v)
    std::unordered_set<std::string> seen;     // för att undvika dubbletter

    for (const auto& [u, neighbors] : adjList) {
        for (const auto& [v, weight] : neighbors) {
            std::string edgeId = (u < v) ? u + "-" + v : v + "-" + u;
            if (seen.count(edgeId)) continue;
            seen.insert(edgeId);
            edges.push_back({weight, u, v});
        }
    }

    // 2. Sortera alla kanter efter vikt
    std::sort(edges.begin(), edges.end());

    // 3. Initiera disjoint sets
    DisjointSets<T> ds(true, true); // path compression + union by rank
    for (const auto& [u, _] : adjList) {
        ds.makeSet(u);
    }

    // 4. Iterera genom sorterade kanter
    for (const auto& [weight, u, v] : edges) {
        if (ds.findSet(u) != ds.findSet(v)) {
            ds.unionSet(u, v);
            mst.push_back({u, v, weight});
            totalCost += weight;
        }
    }
}

template<class T>
void Graph<T>::prims(std::vector<std::tuple<T, T, int>> &mst, int& totalCost)
{
    std::vector<std::tuple<int, T, T>> candidateEdges;
    std::unordered_set<T> visited;
    T start = adjList.begin()->first;
    visited.insert(start);

    // Add edges from start
    for (const auto& [nbr, w] : adjList[start]) {
        candidateEdges.push_back({w, start, nbr});
    }

    while (!candidateEdges.empty() && visited.size() < adjList.size()) {
        // Sort edges by weight
        std::sort(candidateEdges.begin(), candidateEdges.end());

        // Take edge with smallest weight
        auto [weight, u, v] = candidateEdges.front();
        candidateEdges.erase(candidateEdges.begin());

        if (visited.count(v)) continue;

        visited.insert(v);
        mst.push_back({u, v, weight});
        totalCost += weight;

        // Add edges from new node
        for (const auto& [nbr, w] : adjList[v]) {
            if (!visited.count(nbr)) {
                candidateEdges.push_back({w, v, nbr});
            }
        }
    }

}

template<class T>
int Graph<T>::getNrOfVertices() const
{
	return adjList.size();
}

template<class T>
int Graph<T>::getNrOfEdges() const
{
	return edgeCount;
}

template<class T>
std::string Graph<T>::depthFirstSearch(T start) {
    std::vector<T> result;
    std::vector<T> stack = { start };
    std::unordered_map<T, bool> visited;

    while (!stack.empty()) {
        T node = stack.back();
        stack.pop_back();

        if (!visited[node]) {
            visited[node] = true;
            result.push_back(node);

            auto neighbours = getAllNeighboursTo(node);
            std::sort(neighbours.rbegin(), neighbours.rend());

            for (const T& neighbor : neighbours) {
                if (!visited[neighbor])
                    stack.push_back(neighbor);
            }
        }
    }

    std::string traversal;
    for (int i = 0; i < result.size(); ++i) {
        traversal += result[i];
        if (i != result.size() - 1)
            traversal += ",";
    }
    return traversal;
}


template<class T>
std::string Graph<T>::breadthFirstSearch(T start) {
    std::vector<T> result;
    std::vector<T> queue = { start };
    std::unordered_map<T, bool> visited;
    visited[start] = true;

    int index = 0;
    while (index < queue.size()) {
        T node = queue[index++];

        result.push_back(node);

        auto neighbours = getAllNeighboursTo(node);
        std::sort(neighbours.begin(), neighbours.end());

        for (const T& neighbor : neighbours) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push_back(neighbor);
            }
        }
    }

    std::string traversal;
    for (int i = 0; i < result.size(); ++i) {
        traversal += result[i];
        if (i != result.size() - 1)
            traversal += ",";
    }
    return traversal;
}