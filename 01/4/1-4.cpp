#include <iostream>
#include <vector>

void read(int &x) {
    int c = getchar();
    x = 0;
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar());
}

int main() {
    int n, k;
    read(n);
    read(k);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)
        read(a[i]);
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == k) {
            std::cout << i + 1;
            break;
        } else if (a[i] < k)
            --k;
    }
    return 0;
}
