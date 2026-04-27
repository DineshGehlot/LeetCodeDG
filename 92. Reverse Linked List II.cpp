
  struct ListNode {
      int val;
      ListNode *next;
     ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

#include <iostream>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *curr = head, *pre = nullptr, *temp, *leftPointer = nullptr, *rightPointer = nullptr;
        while (--left && curr) {
            leftPointer = curr;
            curr = curr->next;
            --right;
        }
        rightPointer = curr;
        while (--right && curr) {
            temp = curr->next;
            curr->next = pre;

            pre = curr; 
            curr = temp;
        }
        
        if(leftPointer) leftPointer->next = pre;
        if(rightPointer) rightPointer->next = curr;

        return head;
    }

};

int main() {
    Solution sol;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    ListNode *result = sol.reverseBetween(head, 2, 4);
    while (result) {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;
    return 0;
}