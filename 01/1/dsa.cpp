#include "dsa.h"
#include <cstdlib>
#include <functional>
#include <optional>
#include <utility>

namespace part_queue {
    Queue::Queue() : head(0), tail(-1), data() {}

    bool Queue::empty() const { return tail - head == (size_t) -1; }

    std::optional<Value> Queue::pop() {
        if (empty())
            return std::nullopt;
        else {
            size_t ret = data[head];
            head = (size_t) ((++head) % CAPACITY);
            return ret;
        }
    }

    void Queue::push(Value value) {
        tail = (size_t) ((++tail) % CAPACITY);
        data[tail] = value;
    }
} // namespace part_queue
namespace part_stack {
    Stack::Stack() : stack_top(-1), data() {}

    bool Stack::empty() const { return stack_top == (size_t) -1; }

    std::optional<Value> Stack::pop() {
        if (empty())
            return std::nullopt;
        else
            return data[stack_top--];
    }

    void Stack::push(Value value) { data[++stack_top] = value; }
} // namespace part_stack

namespace part_hash_table {
    using Status = Slot::Status;

    HashTable::HashTable(std::function<size_t(Key)> hash_func) : slots() { this->hash_func = std::move(hash_func); }

    std::array<Slot, CAPACITY> HashTable::dump() const { return slots; }

    bool HashTable::insert(Key key, Value value) {
        auto index = (size_t) ((hash_func(key)) % CAPACITY);
        while (slots[index].status != Slot::Status::empty)
            if (slots[index].status != Slot::Status::erased && slots[index].key == key)
                return false;
            else
                index = (size_t) ((++index) % CAPACITY);
        index = (size_t) ((hash_func(key)) % CAPACITY);
        while (slots[index].status == Slot::Status::occupied)
            index = (size_t) ((++index) % CAPACITY);
        slots[index].key = key;
        slots[index].value = value;
        slots[index].status = Slot::Status::occupied;
        return true;
    }

    std::optional<Value> HashTable::lookup(Key key) const {
        auto index = (size_t) ((hash_func(key)) % CAPACITY);
        while (slots[index].status != Slot::Status::empty)
            if (slots[index].key == key)
                return slots[index].value;
            else
                index = (size_t) ((++index) % CAPACITY);
        return std::nullopt;
    }

    bool HashTable::erase(Key key) {
        auto index = (size_t) ((hash_func(key)) % CAPACITY);
        while (slots[index].status != Slot::Status::empty)
            if (slots[index].key == key) {
                slots[index].status = Slot::Status::erased;
                return true;
            } else
                index = (size_t) ((++index) % CAPACITY);
        return false;
    }

} // namespace part_hash_table