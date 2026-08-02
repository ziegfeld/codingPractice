class Solution {
public:
     // optimized. prefix sum array + hash table for counts. note num[i] could be a negative integer!
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1) return nums[0] == k;
        int ans = 0; // answer
        int cur_sum = 0;
        // vector<int> a (n,0); // prefix sum: a[i] means sum nums[0..i]
        std::unordered_map<int, int> cnt; //prefix_counts;
        cnt[0] = 1; // for corner case that sum[0..i] == k. see below.
        for (int i = 0; i<n; i++) {
            // i=2, cnt[-1]=1; cnt[-2]=1;
            // cur_sum= -1.
            cur_sum += nums[i];
            // ask if k == sum[i] - sum[j-1]. know sum[i], just count how many sum[j-1] == sum[i] - k.
            ans += cnt[cur_sum-k];
            cnt[cur_sum]++;
        }
        return ans;
    }
};

/*
naive solution passed OJ:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 1) return nums[0] == k;
        int ans = 0; // answer
        vector<int> a (n,0);
        if ((a[0] = nums[0]) == k) ++ans;
        // auto a(nums);
        for (int i = 1; i<n; i++) {
            if ((a[i]=a[i-1]+nums[i]) == k) ++ans;
            if (nums[i] == k) ++ans;
            for (int j = 0; j<i-1; j++) {
                if (a[i] - a[j] == k) ++ans;
            }
        }
        return ans;
    }

*/
/*
how to DP?

only add nums[i] for once. with it. look back.

sums[x,y] =a[y]-a[x];
if sums==k then ans++;

loop state transfer from last loop:

*/
