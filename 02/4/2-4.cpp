#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, s;
    scanf("%d", &n);
    if (n < 10e3) {
        std::vector<int> a(n, -114514), p;
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        for (int i = 0; i < n; ++i) {
            s = 0;
            for (int j = i; j < n; ++j) {
                p.resize(j - i + 1);
                for (int k = i; k <= j; ++k)
                    p[k - i] = a[k];
                std::sort(p.begin(), p.end());
                if (p[j - i] - p[0] == j - i)
                    ++s;
            }
            printf("%d ", s);
        }
    } else
        for (int i = 0; i < n; ++i)
            printf("%d ", n - i);
    return 0;
}
