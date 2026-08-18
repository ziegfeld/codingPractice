// kinds like 2024 SAPEON codility : https://leetcode.com/discuss/post/1037927/microsoft-online-assessment-codility-by-2ksbq/
/*
Hi All, I took the Microsoft online assessment on 26-JAN-2021 for a Senior Engineer position and below are the questions I got. I had to solve all the questions in 60 minutes.

Given an integer array A[], find the number of elements in the array for which A[i] = number of times A[i] occurs in the array. For example, if A[] = [2,2,4,5,3,3,3] we need to return 2. The number 2 occurs 2 times and 3 occurs 3 times and hence the answer is 2.

We are given a string S of length NN consisting only of letters A and/or B. Our goal is to obtain a string in the format A...AB...B. (all letters A occur before all letters B) by deleting some letters from S. In particular, strings consisting only of letters A or only of letters B fit this format. Write a function that, given a string S, return the minimum number of letters that need to be deleted from S in order to obtain a string in the above format.
N is an integer within the range [1,100,000][1,100000];
string S consists only of the characters A and/or B.

You are given two arrays A and B consisting of N integers each. Index K is named fair if the four sums(A[0]+...A[K-1]),(A[K]+...+A[N-1]),(B[0]+...+B[K-1]) and (B[K]+...+B[N-1]) are all equal, In other words, K is the index where the two arrays, A and B, can be split (into two non-empty arrays each) in such a way that the sums of the resulting arrays’ elements are equal. For example, given arrays A = [4,-1, 0, 3] and B = [-2, 5, 0, 3], index K = 2 is fair. The sums of the subarrays are all equal: 4+(-1) = 3; 0+3 = 3; -2 + 5 = 3 and 0 + 3 = 3. Now you have to figure out the number of fair indexes.
2<=N<=100000
-1000000000<=a[i],b[i]<=1000000000 (0<=i<N)
*/

// https://leetcode.com/problems/find-the-middle-index-in-array/
/*
Runtime
0
ms
Beats
100.00%
Memory
16.77
MB
Beats
17.72%
*/
// https://hackingcpp.com/cpp/std/vector

class Solution {
public:
    int findMiddleIndex(vector<int>& A) {
        const auto n = A.size();
        vector<int> p(n+1,0); // prefix sum
        
        for (int i = 1; i <= n; i++) 
            p[i] = p[i-1] + A[i-1];
        if (p[n] - A[0] == 0) {
            return 0;
        }
        for (int k = 1; k < n - 1; ++k) {
            if (p[k] == p[n] - p[k+1]) {
                return k;
            }
        }
        
        if (n >= 2 && p[n-1] == 0) { // 
            return n-1;
        }

        return -1;
    }

/*
// naive: (note the corner cases.)
        int total = 0;

        for (int x : A) total += x;

        int left = 0;
        int right = total - A[0];
        if (right == 0) {
            return 0;
        }
// total 2, right 3 ; k = 1, left = 1, right = 3-A[1] = 4 
// A.size = 3. K< 2 is ending condition for for loop..
// k = 2: left += -1 ; left = 0; right = 4 - A[2] = 0; return 2.
        for (int k = 1; k < A.size() - 1; ++k) {
            left += A[k - 1];
            right -= A[k];
            if (left == right) {
                return k;
            }
        }
        
        if (A.size() >= 2 && left + A[A.size()-2] == 0) { // or total - A[A.size()-1] == 0
            return A.size()-1;
        }

        return -1;

    }
    */
};
