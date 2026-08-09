

/*
https://leetcode.com/problems/lfu-cache/
460. LFU Cache -- (Hard Difficulty)

solution below
Runtime 82ms
Beats 91.77%
Memory 184.84MB
Beats 84.32%
https://leetcode.com/problems/lfu-cache/solutions/8451302/c-unordered_map-with-iterator-and-splice-kouo

Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

 
*/


#include <unordered_map> // 换成哈希表以达到纯 O(1)，如果必须用 std::map 则是 O(log N)
#include <list>

/* 优化的方向：
1. 彻底消除结构体拷贝（用 std::list::splice 优化 touch）
在之前的代码中，当更新频率时，我们是把节点从旧链表 erase，然后重新创建并 push_front 到新链表。这涉及了内存的释放、重新分配以及结构体拷贝。优化方案：使用 std::list::splice。它可以直接移动整个节点（只改指针指针，不重新分配内存），将节点瞬间从旧链表转移到新链表，性能直接起飞。

2. 避免双重哈希查找（优化 put 中的 find）
原代码中，在 put 发现 key 已经存在时，调用了 touch(it->second)，随后又执行了 cache[key]->value = value。这导致同一个 key 在哈希表中被查找了两次。优化方案：直接利用 it->second（它就是链表迭代器），通过 (*it->second).value = value 直接原地修改，免去第二次查找。

3. 使用 std::unordered_map::reserve 预分配内存
LeetCode 会用成千上万的数据测试你的代码，如果 unordered_map 频繁触发扩容（Rehash），会导致严重的耗时。优化方案：在构造函数中明确调用 reserve(capacity)，强制要求哈希表直接分配好空间，完全消灭运行期间的扩容开销。
*/
class LFUCache {
private:
    struct CacheNode {
        int key;
        int value;
        int count;
    };

    int capacity;
    int minFreq;

    // 主缓存：key -> 链表迭代器
    std::unordered_map<int, std::list<CacheNode>::iterator> cache;
    // 频率表：count -> 该频率的节点链表; biggest count in front.
    std::unordered_map<int, std::list<CacheNode>> freqMap;

    // 使用 splice 达到极致的 O(1) 移动，没有任何内存分配和拷贝
    void touch(std::list<CacheNode>::iterator it) {
        int oldFreq = it->count;
        int newFreq = oldFreq + 1;
        it->count = newFreq; // 更新频率

        // 利用 splice 把当前节点无缝从旧链表切切切换到新链表的头部
        freqMap[newFreq].splice(freqMap[newFreq].begin(), freqMap[oldFreq], it);
        // splice overload ver2: // 版本 2：把 list2 中的【单个节点 it】瞬间移到 list1 的 pos 位置 // list1.splice(list1.begin(), list2, it);  

        // 如果旧频率链表空了，且它刚好是当前的最小频率，更新最小频率
        if (freqMap[oldFreq].empty() && oldFreq == minFreq) {
            minFreq = newFreq;
        }
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {
        // 优化点 3：提前预留空间，防止频繁 rehash
        cache.reserve(capacity + 2);
    }

    int get(int key) {
        if (capacity == 0) return -1;

        auto it = cache.find(key);
        if (it == cache.end()) return -1;

        touch(it->second);
        return it->second->value; // 直接通过迭代器取值，避免再次 find
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        auto it = cache.find(key);

        // 情况 1: key 已经存在
        if (it != cache.end()) {
            it->second->value = value; // 优化点 2：直接原地修改，避免再次查找
            touch(it->second);
            return;
        }

        // 情况 2: 缓存满了
        if (cache.size() >= capacity) {
            auto& minFreqList = freqMap[minFreq];
            int keyToRemove = minFreqList.back().key;
            cache.erase(keyToRemove); // 从哈希表移除
            minFreqList.pop_back();   // 从链表尾部淘汰
        }

        // 情况 3: 插入新元素
        minFreq = 1; // 新元素的频率一定是 1
        freqMap[1].push_front(CacheNode{key, value, 1});
        cache[key] = freqMap[1].begin();
    }
};


// #include <multiset>
// #include <vector>
// #include <queue>

/*
TODO not finished here!
#include <unordered_map>
using MapIt = std::map<int, int>::iterator;
struct CompareCnt {
    bool operator() (const MapIt& a, const MapIt& b) const{
        return a->second < b->second; // ascending order; smallest cnt first aka in front.
    }
}
class LFUCache {
    int capacity;
    std::unordered_map<int, int> cache; // cache[key_aka_tag] = raw_data_value;
    std::multiset<int, std::list<int>::iterator> cnt; // usage count

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            cnt[key]++;
            // recent.erase(pos[key]); // erase from "age fifo"
            // recent.push_front(key); // make it the most recently used (aka front) in "age fifo"
            // pos[key] = recent.begin(); // insert this to key-age map
            return cache[key]; // return value from actual data storage
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // already has this key, so later will update value. 
            // now erase from "age fifo" only
            cnt[key]++;
        } else {
            cnt[key]=1;
            if (recent.size() >= capacity) {
                // eviction as full
                int lfu_key = cnt.begin()->first;
                cache.erase(lfu_key);
                cnt.erase(cnt.begin());   // erase from key-age map
            }
        }
        recent.push_front(key);    // make it the most recently used (aka front) in "age fifo"
        pos[key] = recent.begin(); // update key-age map
        cache[key] = value;        // update key-value pair
    }
};
*/
