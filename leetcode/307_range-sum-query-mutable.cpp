// https://leetcode.com/problems/range-sum-query-mutable/
// segment tree. but not 1 based.
// https://leetcode.com/problems/range-sum-query-mutable/solutions/5344307/segment-tree-or-prefix-tree-with-sparse-update-on-query-sumrange
// with ref to  segment tree implementation previously submitted.
#pragma GCC optimize("03")
class NumArray {
    vector<int> seg;
    int n;

public:
    void built(int i, int l, int h, vector<int>& v) {
        if (l == h) {
            seg[i] = v[l];
            return;
        }
        int m = (l + h) / 2;
        built(i * 2 + 1, l, m, v);
        built(i * 2 + 2, m + 1, h, v);
        seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
    }
    void upd(int i, int l, int h, int ind, int val) {
        if (l == h) {
            seg[i] = val;
            // cout << "seg[" << i << "] - " << l << " aka " << ind << " -> " << val << endl;
            return;
        }
        int m = (l + h) / 2;
        if (ind <= m) {
            upd(2 * i + 1, l, m, ind, val);
        } else {
            upd(2 * i + 2, m + 1, h, ind, val);
        }
        seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
    }

    int solve(int i, int l, int h, int lt, int rt) {
        if (lt > h || rt < l)
            return 0;
        if (lt <= l && rt >= h)
            return seg[i];
        int m = (l + h) / 2;
        int a = solve(i * 2 + 1, l, m, lt, rt);
        a += solve(i * 2 + 2, m + 1, h, lt, rt);
        return a;
    }
    NumArray(vector<int>& nums) {
        n = nums.size();
        seg.resize(4 * nums.size(), 0);
        built(0, 0, nums.size() - 1, nums);
    }

    void update(int index, int val) { upd(0, 0, n - 1, index, val); }

    int sumRange(int left, int right) {
        return solve(0, 0, n - 1, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
/*
class NumArray {
    vector<int> num;
    vector<int> sum;
    int n;
    map<int, int> difmap;
public:
    NumArray(vector<int>& nums) {
        num = nums;
        n = nums.size();
        sum.push_back(num[0]);
        if (n == 1) return;
        for (int i = 1; i < n; ++i) {
            sum.push_back(sum[i-1] + num[i]);
        }
    }

    void update(int index, int val) {
        int diff = val - num[index];
        difmap[index] = diff;
        // num[index] = val;
        // for (int i = index; i < n; ++i) {
        //     sum[i] += diff;
        // }
        // cout << "update done \n";
        // instead of updating each result of sum starting from index;
        // keep a map (ordered, BST tree) to store sparse update index->diff
pairs
        // only when querying range, we can (optionally choose to) update the
sum[] elements, if desired

    }

    int sumRange(int left, int right) {
        // cout << "querying sumRange: " << left << " - " << right << "\n";
        auto itl = difmap.lower_bound(left);
        auto itr = difmap.upper_bound(right);
        int diff_acc = 0;
        if (itl != difmap.end() && itl->first >=left && itl->first <= right) {
            do {
                diff_acc += itl->second;
                // cout << "adding diff_acc for previous update of: " <<
itl->first << " -> diff = " << itl->second << "\n"; itl++; } while (itl != itr
&& itl != difmap.end());
        }
        if (left == 0)
            return sum[right] + diff_acc;
        return sum[right] - sum[left-1] + diff_acc;

    }
    // try 1: 5% time beating percentile
    // void update(int index, int val) {
    //     int diff = val - num[index];
    //     num[index] = val;
    //     for (int i = index; i < n; ++i) {
    //         sum[i] += diff;
    //     }
    //     // cout << "update done \n";
    // }

    // int sumRange(int left, int right) {
    //     // cout << "query of sumRange done \n";
    //     if (left == 0)
    //         return sum[right];
    //     return sum[right] - sum[left-1];

    // }
};


 */
