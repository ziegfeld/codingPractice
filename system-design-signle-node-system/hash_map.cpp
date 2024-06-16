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
