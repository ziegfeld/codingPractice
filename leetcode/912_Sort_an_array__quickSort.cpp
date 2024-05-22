class Solution {
public:
    void swap(int &a, int &b)
    {
        int t=a;
        a = b;
        b = t;
    }
    int partition(vector<int>& a, int left, int right) {
        // int pivot = left, index = pivot + 1;
        // for (int i = index; i <= right; ++i) {
        //     if (a[i] < a[pivot]) {
        //         swap(a[i], a[index]);
        //         ++index;
        //     }
        // }
        // swap(a[pivot], a[index - 1]);
        // return index - 1;
        int randomIndex = left + rand() % ( right - left + 1);
        swap(a[randomIndex], a[left]);
        int pivot = left, index = pivot + 1;
        for (int i = index; i <= right; ++i) {
            if (a[i] < a[pivot]) {
                swap(a[i], a[index]);
                ++index;
            }
        }
        swap(a[pivot], a[index - 1]);
        return index - 1;
    }
    void quickSort(vector<int>& a, int left, int right) {
        if (left < right) {
            int partitionIndex = partition(a, left, right);
            quickSort(a, left, partitionIndex - 1);
            quickSort(a, partitionIndex + 1, right);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        const int n = nums.size();
        if (n > 1)
            quickSort(nums, 0, n - 1);
        return nums;
    }
};
