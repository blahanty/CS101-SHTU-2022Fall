#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void read(int &x) {
    auto c = getchar();
    x = 0;
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar());
}

class Node {
public:
    Node(Node *p, Node *n, int val) : previous(p), next(n), value(val) {}

    int GetValue() const { return value; }

    Node *GetPrevious() const { return previous; }

    Node *GetNext() const { return next; }

    void SetValue(int x) { value = x; }

    void SetPrevious(Node *p) { previous = p; }

    void SetNext(Node *n) { next = n; }

private:
    int value;
    Node *previous, *next;
};

class NodeV {
public:
    NodeV(int i, NodeV *p, NodeV *n) : index(i), previous(p), next(n) {}

    int GetIndex() const { return index; }

    NodeV *GetPrevious() const { return previous; }

    NodeV *GetNext() const { return next; }

    void SetPrevious(NodeV *p) { previous = p; }

    void SetNext(NodeV *n) { next = n; }

private:
    int index;
    NodeV *previous, *next;
};

int main() {
    std::map<int, NodeV *> position;
    int n, t, c = 0, ki, vi, ind, old_value, num;
    auto head = new Node(nullptr, nullptr, -1);
    auto tail = new Node(head, nullptr, -1);
    head->SetNext(tail);
    read(n);
    std::vector<Node *> nodes(n + 1, nullptr);
    std::vector<NodeV *> nodeVs(n + 1, nullptr);
    nodes[0] = head;
    nodes[n] = tail;
    Node *new_node, *old_next, *old_previous, *iter, *next_iter;
    NodeV *new_nodeV, *iterV, *next_iterV;
    for (int i = 0; i < n; ++i) {
        read(t);
        switch (t) {
            case 1:
                read(ki);
                read(vi);
                if (ki > c || nodes[ki] == nullptr) {
                    printf("!\n");
                    break;
                }
                old_next = nodes[ki]->GetNext();
                new_node = new Node(nodes[ki], old_next, vi);
                nodes[ki]->SetNext(new_node);
                old_next->SetPrevious(new_node);
                nodes[++c] = new_node;
                new_nodeV = new NodeV(c, nullptr, position[vi]);
                nodeVs[c] = new_nodeV;
                if (position[vi] != nullptr)
                    position[vi]->SetPrevious(new_nodeV);
                position[vi] = new_nodeV;
                printf("%d %d\n", nodes[ki]->GetValue(), new_node->GetNext()->GetValue());
                break;
            case 2:
                read(ki);
                read(vi);
                if (ki > c || !ki || nodes[ki] == nullptr) {
                    printf("!\n");
                    break;
                }
                old_value = nodes[ki]->GetValue();
                nodes[ki]->SetValue(vi);
                if (nodeVs[ki]->GetPrevious() != nullptr)
                    nodeVs[ki]->GetPrevious()->SetNext(nodeVs[ki]->GetNext());
                else
                    position[old_value] = nodeVs[ki]->GetNext();
                if (nodeVs[ki]->GetNext() != nullptr)
                    nodeVs[ki]->GetNext()->SetPrevious(nodeVs[ki]->GetPrevious());
                if (position[vi] != nullptr)
                    position[vi]->SetPrevious(nodeVs[ki]);
                nodeVs[ki]->SetPrevious(nullptr);
                nodeVs[ki]->SetNext(position[vi]);
                position[vi] = nodeVs[ki];
                printf("%d\n", old_value);
                break;
            case 3:
                read(vi);
                num = 0;
                next_iterV = position[vi];
                while (next_iterV != nullptr) {
                    ind = next_iterV->GetIndex();
                    iter = nodes[ind];
                    old_next = iter->GetNext();
                    old_previous = iter->GetPrevious();
                    old_previous->SetNext(old_next);
                    old_next->SetPrevious(old_previous);
                    delete iter;
                    nodes[ind] = nullptr;
                    iterV = next_iterV;
                    next_iterV = next_iterV->GetNext();
                    delete iterV;
                    nodeVs[ind] = nullptr;
                    ++num;
                }
                position[vi] = nullptr;
                printf("%d\n", num);
                break;
            default:
                break;
        }
    }
    next_iter = head->GetNext();
    while (next_iter != tail) {
        printf("%d ", next_iter->GetValue());
        iter = next_iter;
        next_iter = next_iter->GetNext();
        delete iter;
    }
    delete tail;
    position.clear();
    nodes.clear();
    return 0;
}