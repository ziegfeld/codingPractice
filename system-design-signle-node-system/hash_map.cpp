// with reference to https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/hash_table/hash_map.ipynb
/*
  Constraints and assumptions

For simplicity, are the keys integers only?
Yes
For collision resolution, can we use chaining?
Yes
Do we have to worry about load factors?
No
Can we assume inputs are valid or do we have to validate them?
Assume they're valid
Can we assume this fits memory?
Yes
*/

#include <vector>
using namespace std;
typedef int value_t;
struct kvpair {
  int key;
  value_t value;
}
class HashTable(kvpair) {
  vector<vector<value_t>> m_table;
  HashTable::Hastable(size_t size): m_size(size) {
    m_table.resize(m_size);
  }
  int hash_function(int key) {
    // simple modulo for has_function here
    return key % m_size;
  }

  void set(int key, int value) {
    int hash_index = hash_function(key);
    for (auto item : m_table[hash_index]) {
      if (item.key == key) {
        // found an existing key-val pair, update val only.
        item.value = value;
        return;
      }
    }
    // else, just add this <k,v> pair to this has_index's linked list in hashMap storage table
    m_table[has_index].push_back(new kvpair{key, value}); // new or not here for push_back??
  }

  value_t get(int key) {
    int hash_index = has_function(key);
    for (auto item : m_table[has_index]) {
      if (item.key == key) {
        return item.value;
      }
    }
    raise KeyError('Key not found!'); // find standard c++ error code for this!!
  }
  
  void remove(int key, int value) {
    int hash_index = hash_function(key);
    for (auto item : m_table[hash_index]) {
      if (item.key == key) {
        m_table[hash_index].erase(item); // ???? how to do this with iterator??
        return;
      }
    }
    raise KeyError('Key not found!'); // find standard c++ error code for this!!
  }
}

// another apprach, with resizeTable, with template.
// https://medium.com/@mark.winter/implementing-a-hash-table-in-c-14-for-practice-9c4ad6b7cc3e

template <typename T, typename U>
class BetterHashMap {
public:
    BetterHashMap(std::size_t size=100) : count_(0), resize_limit_(10) {
        table_.reserve(size);
        for (int i = 0; i < size; i++)
            table_.emplace_back();
    }
    
    U get(T key) const {
        auto slot = table_[getSlot(key)];
        return slot.second;
    }
    
    void put(T key, U value) {
        auto& slot = table_[getSlot(key)];
        
        // Found a slot for this key so update its value
        if (slot.first) {
            slot.second = value;
            return;
        }
        
        // Resize if table is almost full
        if (table_.size() - count_ < resize_limit_) {
            resizeTable();
            auto& slot = table_[getSlot(key)];
            slot.first = key;
            slot.second = value;
            count_++;
            return;
        }
        
        // Found empty slot so set key and value
        slot.first = key;
        slot.second = value;
        count_++;
    }
    
private:
    std::vector<std::pair<T, U>> table_;
    std::size_t count_;
    uint8_t resize_limit_;
    
    std::size_t getIndex(T& key) const {
        std::size_t hash = std::hash<T>{}(key);
        return hash % table_.size();
    }
    
    auto getSlot(T& key) const {
        auto index = getIndex(key);
        
        while (table_[index].first != 0 && table_[index].first != key)
            index = (index + 1) % table_.capacity();

        return index;
    }
    
    void resizeTable() {
        // Double our capacity
        table_.reserve(table_.capacity() * 2);
        
        // Add new empty key-pair values for all the new space
        for (int i = 0; i < (table_.capacity() / 2) + resize_limit_; i++)
            table_.emplace_back();
        
        // Reset all the keys
        for (auto& slot : table_) {
            if (slot.first) {
                T first = slot.first;
                U second = slot.second;
                slot = std::pair<T, U>();
                put(first, second);
            }
        }
    }
};
