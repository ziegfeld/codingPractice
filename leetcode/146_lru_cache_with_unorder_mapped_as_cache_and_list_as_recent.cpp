class LRUCache {
    int capacity;
    std::list<int> recent; //recent[index] = lru_age
    std::unordered_map<int, int> cache; // cache[key_aka_tag] = raw_value;
    std::unordered_map<int, std::list<int>::iterator> pos; // pos[key_aka_tag] = iter of this in recent list.
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            recent.erase(pos[key]);
            recent.push_front(key);
            pos[key] = recent.begin();
            return cache[key];
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            recent.erase(pos[key]);
        } else if (recent.size() >= capacity) {
            int last = recent.back();
            recent.pop_back();
            cache.erase(last);
            pos.erase(last);
        }
        recent.push_front(key);
        pos[key] = recent.begin();
        cache[key] = value;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


