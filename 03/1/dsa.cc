#pragma once

#include "dsa.h"

#include <queue>

Graph::Graph(VertexId vertices, std::vector<Edge> edges)
    : vertices(vertices), adj(vertices + 1) {
  for (auto e : edges) adj[e.u].push_back(e);
}

void Graph::sssp(VertexId src, std::vector<Weight> &dis) {
  // TODO
}

void Graph::mst(VertexId src, std::vector<Edge> &mst_edges) {
  // TODO
}