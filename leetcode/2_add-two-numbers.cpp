// number 2: https://leetcode.com/problems/add-two-numbers/description/
// link to this solution: https://leetcode.com/problems/add-two-numbers/solutions/8449770/c-time100-mem-999-tail-the-non-empty-to-634yo

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto ans = l1;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            if (l2 != nullptr) {
                l1->val += l2->val;
                l2 = l2->next; // l2 is next digit now----
            } // else, l2 end; do nothing for l2, but continue below for carry
              // accum..
            if (carry != 0) {
                l1->val++;
                carry = 0;
            }
            if (l1->val > 9) {
                l1->val -= 10;
                carry = 1;
            }
            // l1 = l1->next;
            if (l1->next == nullptr) {   
                // l1 done; advance l2 till the end, plus carry
                if (l2 != nullptr) { // l2 is already next digit now----
                    l1->next = l2;
                    l1 = l1->next; // l1 is next digit now---- and not NULL
                    while (carry != 0) {
                        l1->val++; 
                        carry = 0;
                        if (l1->val > 9) {
                            l1->val -= 10;
                            carry = 1;
                        }
                        if (l1->next == nullptr) { // both numbers done now
                            if (carry != 0) {
                                l1->next = new ListNode(carry);
                                carry = 0;
                            }
                            return ans; // ------end----
                        } else {
                            l1 = l1->next; // l1 is next digit now, ready with
                                           // carry for next loop
                        }
                    }
                    return ans; // ----end ----
                }
                // now l2 == nullptr too; so l1 and l2 all nullptr
                if (carry != 0) {
                    l1->next = new ListNode(carry);
                    carry = 0;
                    l1 = l1->next;
                }
            }
            l1 = l1->next; // now l1 still not null;
        }
        return ans;
    }
};

