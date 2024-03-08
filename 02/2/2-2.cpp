#include <iostream>
#include <vector>

int main() {
    int n, q, val, min = 1145141919, min_index = 0, x, y;
    scanf("%d%d", &n, &q);
    std::vector<int> a(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        scanf("%d", &val);
        if (val < min) {
            min = val;
            min_index = i;
        }
        a[i] = i;
    }
    a[min_index] = -114514;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &x, &y);
        if (x != min_index && y != min_index)
            a[y] = a[x];
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &x, &y);
        if (a[x] == a[y])
            printf("David\n");
        else
            printf("Abigail\n");
    }
    return 0;
}
