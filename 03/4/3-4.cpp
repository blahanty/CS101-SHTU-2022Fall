#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

struct hub {
    int id = 114514, defense = 1919810, bound = 0, days = 1145141919;
    std::vector<int> adj;
    bool visited = false;
};

struct cmp_d {
    bool operator()(const hub &a, const hub &b) {
        return a.days > b.days;
    }
};

struct cmp_b {
    bool operator()(const hub &a, const hub &b) {
        return a.bound > b.bound;
    }
};

int main() {
    int T, n, m, A, D, u, v, ability;
    hub h;
    std::vector<hub> hubs;
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        hubs.clear();
        scanf("%d%d%d%d", &n, &m, &A, &D);
        hubs.resize(n + 1);
        for (int j = 1; j < m + 1; ++j) {
            scanf("%d%d", &u, &v);
            hubs[u].adj.push_back(v);
            hubs[v].adj.push_back(u);
        }
        for (int j = 1; j < n + 1; ++j) {
            scanf("%d", &hubs[j].defense);
            hubs[j].id = j;
        }
        ability = hubs[1].defense;
        hubs[1].defense = -114514;
        hubs[1].days = 0;
        std::priority_queue<hub, std::vector<hub>, cmp_d> heap;
        heap.push(hubs[1]);
        if (A < D) {
            for (auto &hub: hubs)
                hub.bound = (int) floor((ability - hub.defense - 0.114514) / (D - A));
            while (!heap.empty()) {
                h = heap.top();
                heap.pop();
                hubs[h.id].visited = true;
                for (auto &x: h.adj) {
                    if (!hubs[x].visited) {
                        if (hubs[x].days > h.days + 1 && h.days <= hubs[x].bound) {
                            hubs[x].days = h.days + 1;
                            heap.push(hubs[x]);
                        }
                    }
                }
            }
            if (hubs[n].days == 1145141919)
                printf("-1\n");
            else
                printf("%d\n", hubs[n].days);
        } else if (A == D) {
            while (!heap.empty()) {
                h = heap.top();
                heap.pop();
                hubs[h.id].visited = true;
                for (auto &x: h.adj)
                    if (!hubs[x].visited) {
                        if (hubs[x].days > h.days + 1 && hubs[x].defense < ability) {
                            hubs[x].days = h.days + 1;
                            heap.push(hubs[x]);
                        }
                    }
            }
            if (hubs[n].days == 1145141919)
                printf("-1\n");
            else
                printf("%d\n", hubs[n].days);
        } else {
            std::priority_queue<hub, std::vector<hub>, cmp_b> heap2;
            std::set<int> accessible;
            int day = -1;
            for (auto &hub: hubs)
                hub.bound = hub.defense < ability ? 1 : (hub.defense - ability) / (A - D) + 2;
            hubs[1].bound = -114514;
            heap2.push(hubs[1]);
            while (!heap2.empty()) {
                h = heap2.top();
                heap2.pop();
                if (!hubs[h.id].visited) {
                    hubs[h.id].visited = true;
                    if (h.bound <= day + 1) {
                        ++day;
                        accessible.insert(h.id);
                        for (auto &x: h.adj)
                            if (!hubs[x].visited)
                                heap2.push(hubs[x]);
                    } else
                        break;
                }
            }
            for (auto &hub: hubs) {
                hub.days = 1145141919;
                hub.visited = false;
            }
            hubs[1].days = 0;
            while (!heap.empty()) {
                h = heap.top();
                heap.pop();
                if (!hubs[h.id].visited) {
                    hubs[h.id].visited = true;
                    hubs[h.id].days = std::max(hubs[h.id].days, hubs[h.id].bound);
                    for (auto &x: h.adj)
                        if (accessible.find(x) != accessible.end() && !hubs[x].visited &&
                            hubs[x].days > hubs[h.id].days + 1) {
                            hubs[x].days = hubs[h.id].days + 1;
                            heap.push(hubs[x]);
                        }
                }
            }
            if (hubs[n].days == 1145141919)
                printf("-1\n");
            else
                printf("%d\n", hubs[n].days);
        }
    }

    return 0;
}