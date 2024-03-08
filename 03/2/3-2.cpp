#include <iostream>
#include <vector>
#include <algorithm>

struct DisjointSet {
    std::vector<int> parent;

    DisjointSet(int n) {
        parent.resize(n + 1);
        for (int i = 1; i < n + 1; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        return x == parent[x] ? x : (parent[x] = find(parent[x]));
    }

    void merge(int x, int y) {
        parent[find(x)] = find(y);
    }
};

struct Edge {
    int u = 0, v = -114514, w = 1145141919;

    bool operator<(Edge &other) const {
        return w < other.w;
    }
};

int main() {
    int n, m;
    unsigned long long s = 0;
    Edge e;
    scanf("%d%d", &n, &m);
    std::vector<Edge> edges;
    DisjointSet ds(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        scanf("%d", &e.w);
        e.v = i;
        edges.push_back(e);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &e.u, &e.v, &e.w);
        edges.push_back(e);
    }
    std::sort(edges.begin(), edges.end());
    for (auto &edge: edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.merge(edge.u, edge.v);
            s += edge.w;
        }
    }
    printf("%lld", s);
    return 0;
}