// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/
//  3066. Minimum Operations to Exceed Threshold Value II
// my solution new :https://leetcode.com/discuss/topic/5217502/160ms908mbbeats-97-87-priorty_queue-greater-with-mathematical-early-quit-optimization-or-set/
// 160ms|90.8MB|beats 97% 87%| priorty_queue greater with mathematical early quit optimization| or set

// my solution (old): https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/solutions/5213036/c-bst-tree-std-set-with-early-breakout-optimization-10-10
// c++ BST tree std::set with early breakout optimization 10% 10%
// https://leetcode.com/submissions/detail/1269656826/

// #include <algorithm>
// #include <set>
class Solution {
public:
/*
    int minOperations(vector<int>& nums, int k) {
        // all things bigger than k don't care.
        // 2 smallest, then insert back to array if < k
        //using std::set as BST auto balancing

        //end if only 1 element.

        std::multiset<int> s;
        for (auto x : nums) {
            if (x<k) {
                s.insert(x);
            }
        }
        int num_ops = 0;
        // optimization 1: if (2*min1 + min2)/3 >= k_div3, 1 op would result in size-2, not size -1;
        // that means if min1 >= k_div3, just needs to count - num_ops += (s.size() + 1) / 2; add assertion for safety
        const int k_div3 = (k+2)/3; // ceiling

        // cout << "k_div3 = " << k_div3 << "s.size = " << s.size() << endl;
        while (s.size()>1) {
            int min1 = *(s.begin());
            // optimization 1 here..
            if (min1 >= k_div3) {
                // cout << min1 << " is min, >= k_div3 " << k_div3 << " ending early." << endl;
                num_ops +=  (s.size() + 1) / 2;
                break;
            }
            s.erase(s.begin());
            ++num_ops;
            int min2 = *(s.begin());
            s.erase(s.begin());
            int new_num = 2 * min1 + min2;
            // cout << min1 << " and " << min2 << " removed " << endl;
            if (new_num < k) {
                s.insert(new_num);
                // cout << new_num << " inserted, s.size -> " << s.size() << endl;
            // } else {
                // cout << " new element not inserted, s.size -> " << s.size() << endl;
            }
        }
        //[2,11,10,1,3,1,1,2,4,9] - 1, 1, 1, 2, 2,3   op1: 1, 2, 2, 3, + 3;
        // op2: 2 3 3.. op3: 3 3... op4 

        return num_ops + ((s.size() == 1) ? 1 : 0);
    }
};
*/

    int minOperations(vector<int>& nums, int k) {
        // all things bigger than k don't care.
        // 2 smallest, then insert back to array if < k
        // use priority_queue as heap
        //end if only 1 element.

        priority_queue<int, vector<int>, greater<int>> pq; // greater so top of heap is the mininum element, not default max

        for (auto x : nums) {
            if (x<k) {
                pq.push(x);
            }
        }
        int num_ops = 0;
        // optimization 1: if (2*min1 + min2)/3 >= k_div3, 1 op would result in size-2, not size -1;
        // that means if min1 >= k_div3, just needs to count - num_ops += (s.size() + 1) / 2; add assertion for safety
        const int k_div3 = (k+2)/3; // ceiling

        // cout << "k_div3 = " << k_div3 << "pq.size = " << pq.size() << endl;
        while (pq.size() > 1) {
            int min1 = pq.top();
            // optimization 1 here..
            if (min1 >= k_div3) {
                // cout << min1 << " is min, >= k_div3 " << k_div3 << " ending early." << endl;
                num_ops +=  (pq.size() + 1) / 2;
                break;
            }
            ++num_ops;
            pq.pop();
            int min2 = pq.top();
            pq.pop();
            int new_num = 2 * min1 + min2;
            // cout << min1 << " and " << min2 << " removed " << endl;
            if (new_num < k) {
                pq.push(new_num);
                // cout << new_num << " inserted, pq.size -> " << pq.size() << endl;
            } else {
                // cout << " new element not inserted, pq.size -> " << pq.size() << endl;
            }
        }
        return num_ops + ((pq.size() == 1) ? 1 : 0);
    }
};
