#ifndef ZIFMANN_ZGAME_CORE_PACKEDLIST_HPP
#define ZIFMANN_ZGAME_CORE_PACKEDLIST_HPP
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>

namespace zifmann::zgame::core {
template <typename T, size_t N>
class PackedList {
   public:
    inline void push_back(T item) {
        assert(size < N && "List is full");
        items[size++] = item;
    }
    inline void remove(T item) {
        auto pos = std::find(items.begin(), items.end(), item);
        if (pos != std::end(items)) {
            size_t _pos = std::distance(pos, items.begin());
            items[_pos] = items[size--];
        }
    }
    inline void remove_at(size_t pos) { items[pos] = items[size--]; }
    T* begin() { return items.begin(); }
    T* end() { return items.begin() + size; }

   private:
    std::array<T, N> items;
    std::size_t size = 0;
};
}  // namespace zifmann::zgame::core

#endif
