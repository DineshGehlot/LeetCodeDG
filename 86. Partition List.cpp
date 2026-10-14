class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *firstHead = nullptr, *firstCurr = nullptr;
        ListNode *secondHead = nullptr, *secondCurr = nullptr;

        while(head) {
            if(head->val<x) {
                if(!firstHead)
                    firstHead = head;
                else
                    firstCurr->next = head;
                firstCurr = head;
            } else {
                if(!secondHead)
                    secondHead = head;
                else
                    secondCurr->next = head;
                secondCurr = head;
            }
            head = head->next;
        }
        if(secondCurr) secondCurr->next = nullptr;
        if(!firstHead) return secondHead;
        firstCurr->next = secondHead;
        return firstHead;
    }
};