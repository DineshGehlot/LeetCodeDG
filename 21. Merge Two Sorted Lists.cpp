class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1) return list2;
        if(!list2) return list1;

        ListNode temp, *root, *it;
        root = it = &temp;
        while(list1 && list2) {
            if(list1->val < list2->val) {
                it->next = list1;
                list1 = list1->next;
            } else {
                it->next = list2;
                list2= list2->next;
            }
            it = it->next;
        }
        it->next = (list1)?list1:list2;
        return root->next;
    }
};