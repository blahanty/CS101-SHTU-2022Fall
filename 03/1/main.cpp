#pragma once

#include "dsa.h"

#include <queue>

struct vww {
    VertexId vid = 114514;
    Weight wei = 1919810;
};

struct cmp_sssp {
    bool operator()(vww a, vww b) {
        return a.wei > b.wei;
    }
};

struct cmp_mst {
    bool operator()(Edge a, Edge b) {
        return a.w > b.w;
    }
};

Graph::Graph(VertexId vertices, std::vector<Edge> edges)
        : vertices(vertices), adj(vertices + 1) {
    for (auto e: edges) adj[e.u].push_back(e);
}

void Graph::sssp(VertexId src, std::vector<Weight> &dis) {
    for (auto &di: dis)
        di = INF;
    dis[src] = 0;
    VertexId s = src;
    vww p;
    std::vector<int> visited(vertices + 1, 0);
    std::priority_queue<vww, std::vector<vww>, cmp_sssp> d;
    while (!visited[s]) {
        visited[s] = 114514;
        for (auto &e: adj[s]) {
            if (dis[s] + e.w < dis[e.v]) {
                dis[e.v] = dis[s] + e.w;
                p = {e.v, dis[e.v]};
                d.push(p);
            }
        }
        while (!d.empty() && visited[d.top().vid])
            d.pop();
        if (!d.empty()) {
            s = d.top().vid;
            d.pop();
        }
    }
}


void Graph::mst(VertexId src, std::vector<Edge> &mst_edges) {
    mst_edges.resize(vertices - 1);
    VertexId s = src;
    std::vector<int> visited(vertices + 1, 0);
    std::priority_queue<Edge, std::vector<Edge>, cmp_mst> d;
    for (VertexId i = 0; i < vertices - 1; ++i) {
        visited[s] = 114514;
        for (auto &e: adj[s])
            if (!visited[e.v])
                d.push(e);
        while (visited[d.top().v])
            d.pop();
        s = d.top().v;
        mst_edges[i] = d.top();
        d.pop();
    }
}