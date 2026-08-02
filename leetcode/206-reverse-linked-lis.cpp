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
/*
public:
    // adding the new head to new list of reversed nodes everytime.
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        auto cur = head; // 1
        auto next = cur->next; //2
        while (cur->next != nullptr) { 
            cur->next = next->next;   
            next->next = head;
            head = next; 
            next = cur->next;  
        }
        return head;
    }
*/
// best solution, prev, curr, next. just reverse pointing direction of curr every time.
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr != nullptr) {
            ListNode* next = curr->next; // 1. 暂存下一个节点
            curr->next = prev;          // 2. 翻转当前节点的指向
            prev = curr;                // 3. prev 前进一步
            curr = next;                // 4. curr 前进一步
        }
        
        return prev; // 循环结束时，prev 正好指向原链表的尾节点（新链表的头节点）
    }
}; 
