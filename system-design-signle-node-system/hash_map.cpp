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
// via https://medium.com/@mark.winter/implementing-a-hash-table-in-c-14-for-practice-9c4ad6b7cc3e
// added comments, used API from https://leetcode.com/problems/design-hashmap/ and removed template and typename T, U (using T=U=int)
// note it used std::make_pair<>(-1, -1) as default invalid key (key=0 is valid in the test description) - but this can't pass that leetcode online judge, and is not intended to do so.

using namespace std;

// template <typename T, typename U>using namespace std;

class MyHashMap {

private:
    vector<pair<int, int>> m_table;
    size_t m_count;
    uint8_t m_resize_limit;
    size_t getIndex(int& key) const {
        size_t hash = std::hash<int>{}(key);
        // alternative grammar:
        //    std::hash<int> int_hash; size_t has = int_hash(key);
        return hash % m_table.size();
    }

    // this implement doesn't guarentee for corner case where the key is NOT
    // even in hashmap.
    auto getSlot(int& key) const {
        size_t index = getIndex(key);

        // hash collision: "open addressing with linear probing"; instead of
        // linked-list for the same index slot. "This hopefully meant that with
        // the contiguous memory of a vector, and the locality of values using
        // linear probing, the data would often be found in the cpu’s cache."
        while (m_table[index].first != -1 && m_table[index].first != key) {
            index = (index + 1) % m_table.capacity();
            // capacity total number of elements it CAN HOLD. not size() -
            // current number of elements
        }
        return index;
    }

    void resizeTable() {
        // double capacity
        m_table.reserve(m_table.capacity() * 2);
        // Add new empty key-pair values for all the new space
        for (int i = 0; i < m_table.capacity() / 2 + m_resize_limit; ++i) {
            m_table.emplace_back(std::pair<int, int>(-1, -1));
        }

        // reset all the keys
        for (auto& slot : m_table) {
            if (slot.first != -1) {
                auto first = slot.first;
                auto second = slot.second;
                slot = std::pair<int, int>{}; // reset
                put(first, second);           // re-insert
            }
        }
    }

public:
    MyHashMap(size_t size = 100) : m_count(0), m_resize_limit(10) {
        m_table.reserve(size);
        // why the below, as from
        // https://medium.com/@mark.winter/implementing-a-hash-table-in-c-14-for-practice-9c4ad6b7cc3e
        // : Add new empty key-pair values for all the new space
        for (int i = 0; i < size; ++i) {
            m_table.emplace_back(std::pair<int, int>(-1, -1));
        }
        // LZ: all the above reserve() and emplace_back(), why not resize() ??
    }

    int get(int key) {
        auto slot = m_table[getSlot(key)];
        return slot.second;
    }

    void put(int key, int value) {
        auto& slot = m_table[getSlot(key)];

        // found a slot for this key, just update value
        if (slot.first != -1) {
            slot.second = value;
            return;
        }

        // resize if almost full
        if (m_table.size() - m_count < m_resize_limit) {
            resizeTable();
            auto& slot = m_table[getSlot(key)];
            slot.first = key;
            slot.second = value;
            ++m_count;
            return;
        }
        // found empty slot.
        slot.first = key;
        slot.second = value;
        ++m_count;
    }

    void remove(int key) {
        auto slot = m_table[getSlot(key)];
        slot.first = -1;
        slot.second = 0;
        --m_count;
        return;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
