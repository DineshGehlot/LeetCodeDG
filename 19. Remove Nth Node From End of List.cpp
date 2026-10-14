class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *first = head;
        while (n && first) {
            n--;
            first = first->next;
        }
        if(!first) return head->next; // If n == number of nodes, remove first
        ListNode *second = head;
        while(first->next) {  // Stop to pre pointer for easy removal
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return head;
    }
};