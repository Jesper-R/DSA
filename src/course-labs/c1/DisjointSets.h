#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <unordered_map>
#include <iostream>
#include <vector>

template <class T>
class DisjointSets {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
    bool pathCompression;
    bool unionByRank;

public:
    DisjointSets(bool pathCompression = false, bool unionByRank = false);
    int size();
    void makeSet(T u);
    T findSet(T u);
    void unionSet(T u, T v); 
    T getParent(T u);
};

template <class T>
DisjointSets<T>::DisjointSets(bool pathCompression, bool unionByRank)
    : pathCompression(pathCompression), unionByRank(unionByRank) {}

template <class T>
int DisjointSets<T>::size() {
    return parent.size();
}

template <class T>
void DisjointSets<T>::makeSet(T u) {
    if (parent.find(u) == parent.end()) {
        parent[u] = u;
        rank[u] = 0;
    }
}

template <class T>
T DisjointSets<T>::findSet(T u) {
    if (parent[u] != u) {
        if (pathCompression) {
            parent[u] = findSet(parent[u]);
        } else {
            return findSet(parent[u]);
        }
    }
    return parent[u];
}

template <class T>
void DisjointSets<T>::unionSet(T u, T v) {
    T uRoot = findSet(u);
    T vRoot = findSet(v);

    if (uRoot == vRoot) return;

    if (unionByRank) {
        if (rank[uRoot] < rank[vRoot]) {
            parent[uRoot] = vRoot;
        } else if (rank[uRoot] > rank[vRoot]) {
            parent[vRoot] = uRoot;
        } else {
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
    } else {
        parent[vRoot] = uRoot;
    }
}

template <class T>
T DisjointSets<T>::getParent(T u) {
    return parent[u];
}


#endif