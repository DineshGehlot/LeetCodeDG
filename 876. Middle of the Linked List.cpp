class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow = head, *fast=head->next;

        while(fast) {
            slow = slow->next;
            fast = fast->next;
            if (fast) fast = fast->next;
        }
        return slow;
    }
};


/*
Also works:
class Solution {
public:
    ListNode* middleNode(ListNode* head)
    {
        ListNode* slow = head, *fast = head;
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
        
    }
};

*/