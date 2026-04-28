struct ListNode* deleteDuplicates(struct ListNode* head) {
    
    struct ListNode* frontRunner = (struct ListNode*)malloc(sizeof(struct ListNode));
    frontRunner->next = head;
    struct ListNode* curr = head, * pre = frontRunner;
    while (curr) {
        if(curr->next && curr->next->val == curr->val) {
            int val = curr->val;
            while(curr && curr->val == val) curr = curr->next;
            pre->next = curr;
        } else {

            pre = curr;
            curr = curr->next;
        }

    }
    return frontRunner->next;
}
