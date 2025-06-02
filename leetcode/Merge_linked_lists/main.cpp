 #include <iostream>
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* leftList = list1;
        ListNode* rightList = list2;
        ListNode* mergedList{};
        ListNode* currAdding{};
        while(leftList != nullptr && rightList != nullptr)
        {
            if(leftList->val >= rightList->val)
            {
                if(!mergedList) {
                    mergedList = new ListNode(rightList -> val);
                    currAdding = mergedList;
                }
                else {
                    currAdding -> next = new ListNode(rightList -> val);
                    currAdding = currAdding -> next;
                }

                rightList = rightList -> next;
            }
            else{
                if(!mergedList) {
                    mergedList = new ListNode(leftList -> val);
                    currAdding = mergedList;
                }

                else{
                    currAdding -> next = new ListNode(leftList -> val);
                    currAdding = currAdding -> next;
                }
                
                leftList = leftList -> next;
            }                 
        }

        while(leftList)
        {
            if(!currAdding) //Case of not having added to the merge list yet
            {
                mergedList = new ListNode(leftList -> val); 
                currAdding = mergedList;
            }
            
            else
            {
            currAdding -> next = new ListNode(leftList -> val);
            currAdding = currAdding -> next;
            
            }

            leftList = leftList -> next;
        }

        
        while(rightList)
        {
            if(!currAdding)
            {
                mergedList = new ListNode(rightList -> val); 
                currAdding = mergedList;
            }
            
            else
            {
            currAdding -> next = new ListNode(rightList -> val);
            currAdding = currAdding -> next;
            }
            
            rightList = rightList -> next;
        }

        return mergedList;
    }


    int main()
    {
        ListNode* left;

        ListNode* right = new ListNode(0);
        ListNode* ans = mergeTwoLists(left , right);

       std::cout << ans -> val << " " << ans -> next -> val << "\n";
    }
