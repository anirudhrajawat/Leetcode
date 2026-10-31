class Solution {
public:
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != NULL) {
                pq.push(lists[i]);
            }
        }

        ListNode dummy(0);
        ListNode* temp = &dummy;

        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();

            temp->next = node;
            temp = temp->next;

            if (node->next != NULL) {
                pq.push(node->next);
            }
        }

        return dummy.next;
    }
};