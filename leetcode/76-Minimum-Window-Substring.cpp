/*

https://leetcode.com/articles/minimum-window-substring/ http://www.cnblogs.com/grandyang/p/4340948.html

1. 滑动窗口
LeetCode 76 — Minimum Window Substring（Hard）

给定字符串 s 和 t，找出 s 中包含 t 全部字符（含重复次数）的最短子串；若不存在则返回空串。

要求：
O(∣s∣+∣t∣)

练习点：hash map、双指针、何时收缩窗口

面试追问：怎样定义“当前窗口已满足全部需求”？怎样避免每次重新扫描 map？
*/


class Solution {
public:
    string minWindow(string s, string t) {
        int M = s.size();
        int N = t.size();
        unordered_map<char, int> scount;
        unordered_map<char, int> tcount;
        // left and right means [left, right] of s
        // count means the same chars of s[left, right] with t
        int left = 0, right = 0, count = 0;
        int minLen = INT_MAX;
        int resl=INT_MAX;
        // string res;
        for (char c : t)
            ++tcount[c];
        while (right < M) {
            char c = s[right];
            scount[c] += 1;
            if (tcount.count(c) && scount[c] <= tcount[c]) {
                count += 1;
            }
            while (left <= right && count == N) {
                if (minLen > right - left + 1) {
                    minLen = right - left + 1;
                    resl = left; 
                    // res = s.substr(left, minLen);
                }
                char l = s[left];
                scount[l] -= 1;
                if (tcount.count(l) && scount[l] < tcount[l])
                    count -= 1;
                ++left;
            }
            ++right;
        }
        return resl == INT_MAX? "" :s.substr(resl, minLen);
    }
};
