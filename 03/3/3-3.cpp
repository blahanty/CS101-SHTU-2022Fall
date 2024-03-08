#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Importance {
    int a = 114514, d = 1919810;

    bool operator<(const Importance &other) const {
        return a < other.a || (a == other.a && d < other.d);
    }
};

struct cmp {
    bool operator()(const Importance a, const Importance b) const {
        return a.d < b.d;
    }
};

int main() {
    int n, m, s = 0;
    Importance message, apparatus;
    scanf("%d%d", &n, &m);
    std::vector<Importance> messages(n), apparatuses(m);
    std::multiset<Importance, cmp> options;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &message.a, &message.d);
        messages[i] = message;
    }
    std::sort(messages.begin(), messages.end());
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &apparatus.a, &apparatus.d);
        apparatuses[i] = apparatus;
    }
    std::sort(apparatuses.begin(), apparatuses.end());
    auto index = apparatuses.end() - 1;
    for (int i = n - 1; i >= 0; --i) {
        while (index != apparatuses.begin() - 1)
            if (messages[i].a <= (*index).a)
                options.insert(*(index--));
            else
                break;
        auto iter = options.lower_bound(messages[i]);
        if (iter != options.end()) {
            options.erase(iter);
            ++s;
        }
    }
    printf("%d", s);
    return 0;
}
