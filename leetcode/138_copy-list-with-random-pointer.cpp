

// https://leetcode.com/problems/copy-list-with-random-pointer/description/
// see also https://github.com/doocs/leetcode/blob/main/solution/0100-0199/0138.Copy%20List%20with%20Random%20Pointer/README.md 
// https://leetcode.com/problems/copy-list-with-random-pointer/solutions/8453596/c-2-ways-native-and-then-an-optimization-ckei
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:

    Node* copyRandomList(Node* head) {
/*方法二：模拟（空间优化）
在方法一中，我们使用了额外的哈希表来存储原节点和复制节点的对应关系，我们也可以不使用额外的空间，具体做法如下：

遍历原链表，对于每个节点，复制一个新节点并将其插入到原节点和原节点的下一个节点之间。
再次遍历链表，根据原节点的 random 指针，设置新节点的random 指针。
最后将链表拆分为原链表和复制链表。
时间复杂度 O(n)，其中 n 为链表的长度。忽略答案链表的空间占用，空间复杂度 O(1)。
*/
        if (!head) {return nullptr;}
        Node* cur = head;
        while (cur) {
            Node* node = new Node(cur->val);
            node->next = cur->next;
            cur->next = node;
            cur = node->next;
        }
        cur = head;
        while (cur) {
            cur->next->random = (cur->random == nullptr) ? nullptr : cur->random->next;
            cur = cur->next->next;
        }

        cur = head;
        Node* ans = head->next;
        //链表拆分为原链表和复制链表。 (because the original linked list is also checked to make sure not changed after all!)
        while (cur->next != nullptr) {
            Node* node = cur->next; // a node in the new list (ans list)
            //cur 1-> node = 1' ->2->2'->NULL
            cur->next = node->next; //1 -> 2;
            cur = node; // cur is 1'. 1'->2->2'-> null
        }        
        return ans;

/* // naive 2 pass:
        Node* dummy = new Node(0);
        Node* tail = dummy;
        unordered_map<Node*, Node*> d;
        for (Node* cur = head; cur; cur = cur->next) {
            Node* node = new Node(cur->val);
            tail->next = node;
            tail = node;
            d[cur] = node;
        }
        for (Node* cur = head; cur; cur = cur->next) {
            d[cur]->random = cur->random ? d[cur->random] : nullptr;
        }
        return dummy->next;

        
*/        
    }
};
