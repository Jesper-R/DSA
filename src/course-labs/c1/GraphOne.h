//
// Created by Jesper on 5/21/2025.
//

#ifndef GRAPHONE_H
#define GRAPHONE_H

#include <utility>
#include <vector>
#include <climits>
#include <tuple>
#include <string>

#include <unordered_map>
#include <algorithm>
#include <queue>
#include <functional>
#include <stack>
#include <stdexcept>
#include "Priorityqueue.h"
#include "DisjointSets.h"

const int INFINIT_COST = INT_MAX;

using namespace std;

template <class T>
class Graph
{
private:
	// for you decide
    unordered_map<T, vector<pair<T, int>>> adjList;
    int numEdges;

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

template<class T>
Graph<T>::Graph() : numEdges(0)
{
}

template<class T>
void Graph<T>::addVertex(T theNode)
{
    if(!adjList.contains(theNode))
    {
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

    numEdges+=2;
}

template<class T>
std::vector<T> Graph<T>::getAllNeighboursTo(T vertex)
{
	vector<T> neighbours;

    for(auto edge : adjList[vertex])
    {
        neighbours.push_back(edge.first);
    }

    sort(neighbours.begin(), neighbours.end());

    return neighbours;
}

template<class T>
int Graph<T>::getNrOfVertices() const
{
	return adjList.size();
}

template<class T>
int Graph<T>::getNrOfEdges() const
{
	return numEdges;
}

template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
	if (adjList.empty())
	{
		throw std::runtime_error("No vertices to create an MST from");
	}

	vector<tuple<int, T, T>> edges;
	DisjointSets<T> ds;

	// Add all edges with weight first into tuple, then sort them by weight.
	for(auto [v, neighbours] : adjList)
	{
		ds.makeSet(v);
		for(auto [w, weight] : neighbours)
		{
			if (v < w) // ensure edges arent added twice
				edges.emplace_back(weight, v, w);
			ds.makeSet(w); // ensure every node is in a disjoint set
		}
	}

	sort(edges.begin(), edges.end());

	totalCost = 0;
	// Add edges to mst aslong as it doesnt create a cycle
	for(auto [weight, v, w] : edges)
	{
		if(ds.findSet(v) != ds.findSet(w)) // check if they have the same super parent
		{
			ds.unionSet(v, w);
			mst.emplace_back(v, w, weight);
			totalCost += weight;
		}
	}
}

template<class T>
void Graph<T>::prims(std::vector<std::tuple<T, T, int>> &mst, int& totalCost)
{
	if (adjList.empty())
	{
		throw std::runtime_error("No vertices to create an MST from");
	}

	PriorityQueue<tuple<int, T, T>> pq;
	unordered_map<T, bool> visited;

	// Set all vertexes
	for (auto vertex : adjList)
		visited[vertex.first] = false;

	// Pick starting vertex
	T startVertex = adjList.begin()->first;
	visited[startVertex] = true;

	// add all neighbours of startVertex into pq
	for (auto [neighbour, weight] : adjList[startVertex])
		pq.enqueue(make_tuple(weight, startVertex, neighbour));

	totalCost = 0;
	while (!pq.isEmpty())
	{
		auto [weight, from, to] = pq.peek();
		pq.dequeue();

		if (!visited[to])
		{
			mst.emplace_back(from, to, weight);
			totalCost += weight;
			visited[to] = true;

			for (auto [neighbour, newWeight] : adjList[to])
				if (!visited[neighbour])
					pq.enqueue(make_tuple(newWeight, to, neighbour));
		}
	}
}

template <class T>
std::string Graph<T>::depthFirstSearch(T from)
{
	if (!adjList.contains(from))
	{
		throw std::runtime_error("Starting vertex from not found in graph");
	}
	stack<T> stack;
	unordered_map<T, bool> visited;
	string result;

	// Mark all vertices from adjList as not yet visited
	for (auto vertex : adjList)
	{
		visited[vertex.first] = false;
	}

	stack.push(from); // Start by putting fromVertex on top of stack

	while (!stack.empty())
	{
		T currentVertex = stack.top();
		stack.pop(); // visiting currentVertex

		if (!visited[currentVertex])
		{
			visited[currentVertex] = true;
			result += currentVertex + ",";

			// Create vector of currentVertex neighbouring nodes, if they have not yet been visited, push onto stack.
			vector<T> neighbours = getAllNeighboursTo(currentVertex);
			sort(neighbours.rbegin(), neighbours.rend());
			for (auto neighbour : neighbours)
			{
				if (!visited[neighbour])
				{
					stack.push(neighbour);
				}
			}
		}
	}
	result.pop_back(); // Få väck de där sista jävla kommatecknet
	return result;
}

template <class T>
std::string Graph<T>::breadthFirstSearch(T from)
{
	if (!adjList.contains(from))
	{
		throw std::runtime_error("Starting vertex from not found in graph");
	}
	queue<T> queue; // visit nodes in FIFO-order
	unordered_map<T, bool> visited;
	string result;

	for (auto vertex : adjList)
	{
		visited[vertex.first] = false;
	}

	queue.push(from);
	visited[from] = true; // marked as visited immediately so its not added again
	while (!queue.empty())
	{
		T currentVertex = queue.front();
		queue.pop();
		result += currentVertex + ",";

		vector<T> neighbours = getAllNeighboursTo(currentVertex);
		sort(neighbours.begin(), neighbours.end());

		for (auto neighbour : neighbours)
		{
			if (!visited[neighbour])
			{
				queue.push(neighbour);
				visited[neighbour] = true;
			}
		}
	}
	result.pop_back();
	return result;
}


#endif
