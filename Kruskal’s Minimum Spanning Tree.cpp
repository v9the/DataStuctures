﻿//Kruskal’s Minimum Spanning Tree

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

template <typename T, typename T2>
class Graph {
public:
	vector<pair<T, pair<T, T2>>> adjList;
	vector<T> parent;
	vector<T> rank;
	Graph(T V) {
		/*adjList = vector<vector<pair<T, T2>>>(V);
		adjList2 = vector<vector<pair<T, T2>>>(V);*/
		parent = vector<T>(V);
		rank = vector<T>(V, 0);
		for (int i = 0; i < V; i++)
			parent[i] = i;
	}
	void addEdge(T u, T v, T2 w) {
		adjList.push_back({ u,{ v,w } });
		adjList.push_back({ v,{ u,w } });
	}
	static bool cmp(const pair<T, pair<T, T2>>& a, const pair<T, pair<T, T2>>& b) {
		return a.second.second < b.second.second;
	}
	T find(T node) {
		if (parent[node] == node)
			return node;
		parent[node] = find(parent[node]);
		return parent[node];
	}
	void merge(T node, T node2) {
		T node_parent = find(node);
		T node2_parent = find(node2);
		if (node_parent == node2_parent)
			return;
		if (rank[node_parent] < rank[node2_parent])
			parent[node_parent] = node2_parent;
		else
			parent[node2_parent] = node_parent;
		if (rank[node_parent] == rank[node2_parent])
			rank[node_parent]++;
	}
	T2 kruskal() {
		sort(adjList.begin(), adjList.end(), cmp);
		T2 weight = 0;
		for (auto a : adjList)
			if (find(a.second.first) != find(a.first)) {
				weight += a.second.second;
				merge(a.second.first, a.first);
			}
		return weight;
	}
};

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int n, e;
	cin >> n >> e;
	Graph<int, ll> g(n);
	for (int i = 0; i < e; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}
	ll w = g.kruskal();
	cout << w;
}
