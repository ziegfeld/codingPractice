#include <stack>
class Solution {
    // Runtime 11 ms Beats 94.69%
    // Memory 102.76 MB Beats 91.31%
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        std::stack<int> st; // index of the singly increasing temp array.
        st.push(n-1);
        vector<int> ans(n, 0);
        for (int i = n - 2; i >= 0; i--) {
            while (!st.empty() && temperatures[i] >= temperatures[st.top()]) {
                st.pop();
            }
            if (st.empty()) {
                ans[i] = 0;
            } else {
                ans[i] = st.top() - i;
            }
            st.push(i);
        }
        return ans;


/* passed. but should not have stored the value of temp! and gap! it's in input vector!
include deque not stack (forgot std::stack exists..)
   vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        std::deque<int> st{temperatures[n - 1]};
        std::deque<int> gaps{1}; // _i_to_i_plus1 in st.
        vector<int> ans(n, 0);
        for (int i = n - 2; i >= 0; i--) {
            int gap = 1;
            // bool f = false;
            while (!st.empty() && temperatures[i] >= st.front()) {
                st.pop_front();
                gap += gaps[0];
                gaps.pop_front();
                // f=true;
            }
            // if (f== false && !st.empty()) { ans!=0}
            st.push_front(temperatures[i]);
            gap = st.size() == 1 ? 1 : gap;

            if (st.size() == 1) {
                ans[i] = 0;
                gap = 1; // only 1 element, then no gap to its next in stack
            } else {
                ans[i] = gap;
            }
            gaps.push_front(gap);
        }
        return ans;

*/
        /*
        reverse:
        73: i=7. ans[7]=0. stack: 73
        76: i=6. top of stacK:73<76, no other, ans[7]=0 stack:76
        72: i=5 top of stack 76>72. good, ans[7]=1 stack: 72, 76 (days between
        72-76:0) 1, 1 69: i=4 top of stack 72>69. good, ans[7]=1 stack: 69, 72,
        76 (days between 0,0) 1, 1, 1 71: i=3 top of stack 69, <71, pop 69. then
        72: > 71. good . good, ans[7]=2 stack: 71, 72, 76 (daysbetween 71,72 is
        1!) 2, 1, 1 75: i=2 top of stack pop 71,72 then push 75.   ans[7]=4
        stack: 75, 76 (days between 75,76 is 4(poped 2, +prev1))


        */
    }
};
