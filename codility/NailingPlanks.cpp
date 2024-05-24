//correct but time O(N*M) out of performance check
//  NailingPlanks
// https://app.codility.com/programmers/lessons/14-binary_search_algorithm/nailing_planks/
// Count the minimum number of nails that allow a series of planks to be nailed.
// Binary Search algorithm
// you can use includes, for example:
#include <map>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A, vector<int> &B, vector<int> &C) {
    // Implement your solution here
    // intuition: sort by left edge (A[]), for each nail, commpare if it's >=left_edge, then if <=right_edge; if so, mark this plank nailed.
    // can use containers like some map using BST, key left, value right; if nailed, remove (erase(key))

    const int n = A.size();
    std::multimap<int, int> mm {};
    for (int i = 0; i < n; i++) {
        mm.insert({A[i], B[i]});
        // std::cout << A[i] << " " << B[i] << std::endl;
    }

    int i = 0;
    for (const auto& nail : C) {
        ++i;
        // find all iterators that has left <=nail
        auto itl = mm.lower_bound(1);
        const auto itr = mm.upper_bound(nail);
        if (itl != mm.end() && itl != itr) {
            // std::cout << i << " found left <= nail pos: " << nail << " \n";
            do {
                if (nail <= itl->second) {
                    // std::cout << "found right\n";
                    const auto tmp = itl;
                    itl++;
                    // std::cout << i << " erasing " << tmp->first << " "
                    // << tmp->second << "\n";
                    mm.erase(tmp);
                }
                else {
                    itl++;
                }
            } while (itl != itr && itl !=mm.end());

            if (mm.empty()) {
                return i;
            }
        }
    }
    return -1;
    // improve: just need to find smallest common plank length-span??
    // segment tree
}

// prefix sum: from csdn
// you can also use includes, for example:
// #include <algorithm>
int solution(vector<int> &A, vector<int> &B, vector<int> &C) {
    // write your code in C++98
    int m = C.size();
    int M = (m << 1) | 1;
    int left = 0, right = m, result = -1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        vector<int> v;
        v.resize(M, 0);
        for (int i = 0; i < mid; ++i) {
            ++v[C[i]];
        }
        for (int i = 1; i < M; ++i) {
            v[i] += v[i - 1];
        }
        bool can = true;
        for (int i = 0; i < A.size(); ++i) {
            if (v[B[i]] - v[A[i] - 1] == 0) {
                can = false;
                break;
            }
        }
        if (can) {
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;

// 原文链接：https://blog.csdn.net/caopengcs/article/details/41834173
