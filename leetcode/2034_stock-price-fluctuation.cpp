// https://leetcode.com/problems/stock-price-fluctuation/description/
// my solution:
// https://leetcode.com/problems/stock-price-fluctuation/solutions/5359314/c-hashmap-2-priority-queues-for-max-and-min-lazy-deletion-296-ms-167mb/
/*
2034. Stock Price Fluctuation 
Solved
Medium

Topics
Companies

Hint
You are given a stream of records about a particular stock. Each record contains a timestamp and the corresponding price of the stock at that timestamp.

Unfortunately due to the volatile nature of the stock market, the records do not come in order. Even worse, some records may be incorrect. Another record with the same timestamp may appear later in the stream correcting the price of the previous wrong record.

Design an algorithm that:

Updates the price of the stock at a particular timestamp, correcting the price from any previous records at the timestamp.
Finds the latest price of the stock based on the current records. The latest price is the price at the latest timestamp recorded.
Finds the maximum price the stock has been based on the current records.
Finds the minimum price the stock has been based on the current records.
Implement the StockPrice class:

StockPrice() Initializes the object with no price records.
void update(int timestamp, int price) Updates the price of the stock at the given timestamp.
int current() Returns the latest price of the stock.
int maximum() Returns the maximum price of the stock.
int minimum() Returns the minimum price of the stock.
*/

class StockPrice {
    // unordered_map (hashMap) of time -> price
    unordered_map<int, int> mp;

    // use what container for random insert/delete?  + also ordered by price value
    // red-black tree? min/max tree? 2 priority queues?
    // 2 pq : 1 normal greatest pq, another minimum pq
    // pq's data is pair<price, time>  --- or <price, unordered_set of timestamps> if that's faster.-- try only later!
    using el_t = pair<int, int>;
    // Using lambda to compare elements.
    // auto cmp = [] (el_t left, el_t right) { return left.first < right.first;}
    // auto cmp_gt = [] (el_t left, el_t right) { return left.first > right.first;}
    // std::priority_queue<el_t, std::vector<el_t>, decltype(cmp)> pq(cmp);
    // std::priority_queue<el_t, std::vector<el_t>, decltype(cmp_gt)> pqmin(cmp_gt);
    std::priority_queue<el_t, std::vector<el_t>> pq;
    std::priority_queue<el_t, std::vector<el_t>, greater<el_t>> pqmin;
    int timenow;
    int pricenow;
 
public:
    StockPrice() {
        timenow = 0; pricenow = 0;
    }
    
    void update(int timestamp, int price) {
        mp[timestamp] = price;
        if (timenow < timestamp) {
            timenow = timestamp;
            pricenow = price;
        } else if (timenow == timestamp) {
            pricenow = price;
        }

        pq.push({price, timestamp});
        pqmin.push({price, timestamp});


        // max heap - lazy pop
        while (!pq.empty() && mp[pq.top().second] != pq.top().first) {
            pq.pop();
        }
        //min heap - lazy pop
        while (!pqmin.empty() && mp[pqmin.top().second] != pqmin.top().first) {
            pqmin.pop();
        }
    }
    
    int current() {
        return pricenow;
        
    }
    
    int maximum() {
        return pq.top().first;
        
    }
    
    int minimum() {
        return pqmin.top().first;
        
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
