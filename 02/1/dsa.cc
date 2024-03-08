#include "dsa.h"
#include <cstdio>
#include <cstdlib>

#define TODO()                                                                 \
  do {                                                                         \
    fprintf(stderr, "NOT IMPLEMENTED %s:%d", __FILE__, __LINE__);              \
    std::exit(1);                                                              \
  } while (0)

namespace lsort {
    void merge(const List &la, const List &lb, List &out) {
        auto i1 = la.begin(), i2 = lb.begin();
        out.resize(list_size(la) + list_size(lb));
        auto k = out.begin();
        while (i1 != la.end() && i2 != lb.end())
            if (*i1 < *i2)
                *k++ = *i1++;
            else
                *k++ = *i2++;
        for (; i1 != la.end(); ++i1)
            *k++ = *i1;
        for (; i2 != lb.end(); ++i2)
            *k++ = *i2;
    }

    void partition(const List &la, List &leq, List &gt, Key pivot) {
        for (Key k: la)
            if (k > pivot)
                gt.push_front(k);
            else
                leq.push_front(k);
    }

    Key select_pivot(const List &la) {
        auto index = random_index(list_size(la));
        auto k = la.begin();
        for (int i = 0; i < index; ++i)
            ++k;
        return *k;
    }
} // namespace lsort
