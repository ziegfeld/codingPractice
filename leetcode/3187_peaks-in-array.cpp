// https://leetcode.com/problems/peaks-in-array/description/
// segment tree session
// hard
//
// my solution https://leetcode.com/problems/peaks-in-array/solutions/5354216/608ms-257mb-segment-tree-lazy-update-with-peak-i-bool-array-logging-std-cout
/*

3187. Peaks in Array
Solved
Hard

Topics
Companies

Hint
A peak in an array arr is an element that is greater than its previous and next element in arr.

You are given an integer array nums and a 2D integer array queries.

You have to process queries of two types:

queries[i] = [1, li, ri], determine the count of peak elements in the 
subarray
 nums[li..ri].
queries[i] = [2, indexi, vali], change nums[indexi] to vali.
Return an array answer containing the results of the queries of the first type in order.

Notes:

The first and the last element of an array or a subarray cannot be a peak.

  */

// #pragma GCC optimize ("O3")
class Solution {
    //The first and the last element of an array or a subarray cannot be a peak.
    // segment tree 4*n size
    // also need to store single peak vector of the array size of n
    vector<bool> peak;
    vector<int> seg;
    int n;
    void build(int i, int l, int h, int ll, int hh, vector<int>& num){
        if (l == h) {
            seg[i] = peak[l];
            if (seg[i] == 1) {
                // cout << "build seg[" << i << "] - " << l << " -> updating to " << 1 << endl;
            }
            return;
        }
        int m = (l+h) >> 1;
        build(i*2, l, m, ll, hh, num);
        build(i*2+1, m+1, h, ll, hh, num);
        seg[i] = seg[i*2] + seg[i*2+1];
        return;
    }

    void upd(int i, int l, int h, int lupd, int rupd, vector<int>& num){
        if (l > rupd || h < lupd) {
            return;
        }
        if (l == h) {
            // if (l > 1 && l < n && num[l] > num[l-1] && num[l] > num[l+1]) {
            //     // cout << "upd seg[" << i << "] - " << l << " -> updating to " << 1 << endl;
            //     seg[i] = 1;
            // }
            // else {
            //     // cout << "upd seg[" << i << "] - " << l << " -> updating to " << 0 << endl;
            //     seg[i] = 0;
            // }
            // cout << "upd seg[" << i << "] - " << l << " -> updating from " << seg[i] << " to " << (peak[l] ? 1 : 0)<< endl;
            seg[i] = peak[l];
            return;
        }
        int m = (l+h) >> 1;
        upd(i*2, l, m, lupd, rupd, num);
        upd(i*2+1, m+1, h, lupd, rupd, num);
        seg[i] = seg[i*2] + seg[i*2+1];
        return;
    }

    int query(int i, int l, int h, int ll, int hh, vector<int>& num){
        if (l > hh || h < ll) {
            // cout << "query i= " << i << " l=" <<l << " h=" << h << " ll=" << ll <<" hh=" <<  hh << " exclusive ans: " << 0 << endl;
            return 0;
        }
        if (ll <= l && hh >= h) {
            // cout << "query i= " << i << " l=" <<l << " h=" << h << " ll=" << ll <<" hh=" <<  hh << " inclusive ans: " << seg[i] << endl;
            return seg[i];
        }
        int m = (l+h) >> 1;
        int ans = query(i*2, l, m, ll, hh, num);
        ans += query(i*2+1, m+1, h, ll, hh, num);
        // cout << "query i= " << i << " l=" <<l << " h=" << h << " ll=" << ll <<" hh=" <<  hh << " calc'd ans: " << ans << endl;
        return ans;
    }

public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        // num = nums;
        n = nums.size();
        nums.insert(nums.begin(),0); // do not use position 0. starts from 1.
        //build peak
        peak.resize(n+2);
        {
            short prev_gt = 0; // -1: prev < next; 0: ==, 1: prev>next.
            short this_gt = (nums[1] < nums[2]) ? -1 : ((nums[1] > nums[2]) ? 1 : 0);
            for (int i = 2; i < n; i++) {
                prev_gt =  this_gt;
                this_gt = (nums[i] < nums[i+1]) ? -1 : ((nums[i] > nums[i+1]) ? 1 : 0);
                if (prev_gt == -1 && this_gt == 1) {
                    peak[i] = true;
                    // cout << "build peak[" << i << "] - true"  << endl;
                }
            }
        }
        // build seg tree
        seg.resize(n*4); // default 0's
        build(1,1,n, 1, n, nums);
        vector<int> ans;
        for (auto q : queries) {
            switch (q[0]) {
                case 1: { // query peak sub-array
                    if (q[2]-q[1]<2) {
                        ans.push_back(0);
                        break;
                    }
                    q[1]++; q[2]++;
                    int ans_seg = query(1,1,n,q[1],q[2], nums);
                    // cout << "query for [" << q[1] << "," << q[2] << "] - seg= " << ans_seg << endl;
                    // if (ans_seg == 0) {
                    //     ans.push_back(0);
                    //     break;
                    // }
                    // handle l, h ends corner case!
                    int ans_lt = peak[q[1]];
                    // cout << "query for [" << q[1] << "," << q[2] << "] = seg-lnode= " << ans_seg << " - " << ans_lt
                        // << endl;
                    // if (ans_seg-ans_lt == 0) {
                    //     ans.push_back(0);
                    //     break;
                    // }
                    int ans_rt = peak[q[2]]; // was query(1,1,n,q[2],q[2], nums);
                    // cout << "query for [" << q[1] << "," << q[2] << "] = seg-lnode-rnode= " << ans_seg << " - " << ans_lt
                    //     << " - " << ans_rt << endl;
                    ans.push_back(ans_seg-ans_lt-ans_rt); 
                    break;
                }
                case 2: { // update
                    auto ind = q[1] + 1;
                    auto old = nums[ind];
                    if (old == q[2]) break;
                    nums[ind] = q[2];
                    int new_peak_left = (ind>2) && (nums[ind-2]< nums[ind-1]) && (nums[ind-1] > q[2]);
                    int new_peak_this = (ind>1) && (ind<n) && (nums[ind-1]<q[2]) && (q[2]>nums[ind+1]);
                    int new_peak_right = (ind<=n-2) && (q[2] < nums[ind+1]) && (nums[ind+1] > nums[ind+2]);
                    int qlow = n+1;
                    int qhigh = 0;
                    if (new_peak_left != peak[ind-1]) {
                        // cout << "pre-upd num[" << ind << "] from " << old << " -> " << q[2] << " --peak_left changed from " << peak[ind-1]
                        //     << " to " << new_peak_left << endl;
                        peak[ind-1] = new_peak_left;
                        qlow = ind-1;
                        qhigh = qlow;
                    }
                    if (new_peak_this != peak[ind]) {
                        // cout << "pre-upd num[" << ind << "] from " << old << " -> " << q[2] << " --peak_this changed from " << peak[ind]
                        //     << " to " << new_peak_this << endl;
                        peak[ind] = new_peak_this;
                        qlow = min(qlow,ind);
                        qhigh = max(qhigh,ind);
                    }
                    if (new_peak_right != peak[ind+1]) {
                        // cout << "pre-upd num[" << ind << "] from " << old << " -> " << q[2] << " --peak_next changed from " << peak[ind+1]
                        //     << " to " << new_peak_right << endl;
                        peak[ind+1] = new_peak_right;
                        qlow = min(qlow,ind+1);
                        qhigh = max(qhigh,ind+1);
                    }
                    if (qlow <= qhigh && qlow > 0 && qhigh < n+1) {
                        // cout << "calling upd: qlow to qhigh - (" << qlow << "," << qhigh << ")" << endl;
                        upd(1, 1, n, qlow, qhigh, nums);
                    }


                    // bool leftNochange = (ind == 1);
                    // if (!leftNochange) {
                    //     int diff_old = old - nums[ind-1];
                    //     int diff = q[2] - nums[ind-1];
                    //     leftNochange = ((diff_old > 0 && diff > 0) || (diff_old < 0 && diff < 0) || (diff_old == 0 && diff == 0));
                    // }
                    // bool rightNochange = (ind == n); // overflow: || ((old - num[ind+1])*(q[2]-num[ind+1]) > 0);
                    // if (!rightNochange) {
                    //     int diff_old = old - nums[ind+1];
                    //     int diff = q[2] - nums[ind+1];
                    //     rightNochange = ((diff_old > 0 && diff > 0) || (diff_old < 0 && diff < 0) || (diff_old == 0 && diff == 0));
                    // }
                    // // can optimize for ind == 1 or n -- itself may not need to update either in 2nd and 3rd call to upd() below.
                    // // cout << leftNochange << " " << rightNochange << " for upd ind(+1)=" << ind << endl;
                    // if (!leftNochange && !rightNochange) {
                        
                    //     // cout << "0 0 upd: ind-1 = " << ind-1 << " max(ind-1,1)=" << max(ind-1,1) << endl;
                    //     upd(1, 1, n, max(ind-1,1), min(ind+1,n), nums);
                    // } else if (!leftNochange) { // only ind and left neighbor change
                    //     upd(1, 1, n, max(ind-1,1), ind, nums);
                    // } else  if (!rightNochange) { // only ind and right neighbor change
                    //     upd(1, 1, n, ind, min(ind+1,n), nums);
                    // }
                    break;
                }
                default:
                    assert(0);
            }
        }
        return ans;
    }
};
