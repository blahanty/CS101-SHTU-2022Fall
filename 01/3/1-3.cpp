#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k, v;
    std::cin >> n >> k;
    std::vector<int> cache(k, -114514);
    int h = 0, c = k - 1, l1 = k - 2, l2 = k - 3;
    for (int i = 0; i < n; ++i) {
        std::cin >> v;
        if (k < 3) {
            std::cout << v << " ";
            continue;
        }
        ++c %= k;
        if (c == h && cache[h] >= 0) {
            std::cout << cache[h++] << " ";
            h %= k;
        }
        cache[c] = v;
        ++l1 %= k;
        ++l2 %= k;
        if (cache[c] == cache[l1] && cache[c] == cache[l2] && cache[c] >= 0) {
            cache[c] = -114514;
            cache[l1] = -114514;
            cache[l2] = -114514;
            c = (c + k - 3) % k;
            l1 = (l1 + k - 3) % k;
            l2 = (l2 + k - 3) % k;
        }
    }
    while (cache[h] >= 0) {
        std::cout << cache[h] << " ";
        cache[h++] = -114514;
        h %= k;
    }
    return 0;
}
