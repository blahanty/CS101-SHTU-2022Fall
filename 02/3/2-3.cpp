#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define ull unsigned long long

int n, m;
std::vector<int> a;

class Node {
public:
    Node(int r, int x, int y, ull s) : recent(r), index_l(x), index_r(y), sum(s) {}

    bool CanAddLeft() const { return (!recent && index_l + 1 < n) || (recent && index_l + 1 < index_r); }

    bool CanAddRight() const { return recent < m - 1 && m - recent - 1 < index_l; }

    Node AddLeft() const {
        Node left(recent, index_l + 1, index_r, sum - a[index_l] + a[index_l + 1]);
        return left;
    };

    Node AddRight() const {
        Node right(recent + 1, m - recent - 1, index_l, sum - a[m - recent - 2] + a[m - recent - 1]);
        return right;
    };

    ull GetSum() const {
        return sum;
    }

private:
    int recent, index_l, index_r;
    ull sum;
};

struct cmp {
    bool operator()(const Node &lhs, const Node &rhs) {
        return lhs.GetSum() < rhs.GetSum();
    }
};

int main() {
    int k;
    ull sum_importance = 0;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<int> temp(n, -114514);
    a = temp;
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    std::sort(a.begin(), a.end(), std::greater());
    std::priority_queue<Node, std::vector<Node>, cmp> importance;
    std::vector<int> set(m, 0);
    for (int i = 0; i < m; ++i) {
        set[i] = i;
        sum_importance += a[i];
    }
    Node new_node(0, m - 1, -114514, sum_importance);
    importance.push(new_node);
    for (int i = 0; i < k; ++i) {
        if (importance.empty()) {
            printf("-1");
            return 0;
        }
        new_node = importance.top();
        importance.pop();
        if (new_node.CanAddLeft())
            importance.push(new_node.AddLeft());
        if (new_node.CanAddRight())
            importance.push(new_node.AddRight());
    }
    printf("%lld", new_node.GetSum());
    return 0;
}
