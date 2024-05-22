class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int num_pairs = 0;
        std::unordered_map<int, int> mp {};
        for (auto& val : nums) {
            if (mp.count(k-val) != 0 && mp[k-val]>=1) {
                num_pairs++;
                mp[k-val]--;
            } else {
                mp[val]++;
            }
        }
        return num_pairs;
    }
};
