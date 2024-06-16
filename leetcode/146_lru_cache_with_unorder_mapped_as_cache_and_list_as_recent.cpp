// https://leetcode.com/problems/lru-cache/
/*
146. LRU Cache

Medium

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.


 */

#include <unordered_map>
#include <vector>
#include <queue>

class LRUCache {
    int capacity;
    std::list<int> recent; //recent[i] = key - front() is most recently used; back() is lru. it's like an "age fifo" with random access(for erase only)
    std::unordered_map<int, int> cache; // cache[key_aka_tag] = raw_data_value;
    std::unordered_map<int, std::list<int>::iterator> pos; // pos[key_aka_tag] = iter of this in recent list (a map for age).
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            recent.erase(pos[key]); // erase from "age fifo"
            recent.push_front(key); // make it the most recently used (aka front) in "age fifo"
            pos[key] = recent.begin(); // insert this to key-age map
            return cache[key]; // return value from actual data storage
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // already has this key, so later will update value. 
            // now erase from "age fifo" only
            recent.erase(pos[key]);
        } else if (recent.size() >= capacity) {
            // eviction as full
            int last = recent.back();
            recent.pop_back(); // erase from "age" storage
            cache.erase(last); // erase key-value pair from actual data storage
            pos.erase(last);   // erase from key-age map
        }
        recent.push_front(key);    // make it the most recently used (aka front) in "age fifo"
        pos[key] = recent.begin(); // update key-age map
        cache[key] = value;        // update key-value pair
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
