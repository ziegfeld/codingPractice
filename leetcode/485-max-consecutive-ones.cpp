//https://leetcode.com/problems/max-consecutive-ones/

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& A) {

        int maxl = 0;
        int left = -1;
        // 2 cases when you see A[i](0/1) : already in seq, not in seq.
        for (int i = 0; i < A.size(); i++) {
            if (A[i] == 0) {
                if (left >= 0) {
                    if (i - left > maxl) {
                        maxl = i - left;
                    }
                    left = -1;
                }
            } else { // A[i] == 1
                if (left == -1) {
                    left = i;
                }
            }
        }
        if (left != -1 && A.size() - left > maxl) {
            maxl = A.size() - left;
        }
        return maxl;
    }
};

/* recommended AI for another similar sapion 2024 codility task 4 (2nd programming task:
    int best = -1;
    int current = 0;

    for (int x : A) {
        if (x < 0) {
            current = 0;
        } else {
            current += x;
            best = max(best, current);
        }
    }

    return best;
}
*/

