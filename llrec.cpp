#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    // Base case: if the list is empty, return
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }
    // Place the current node in the appropriate list
    if (head->val > pivot) {
        larger = head;
        head = head->next;
        llpivot(head,smaller,larger->next,pivot);
    } 
    else {
       smaller = head;
       head = head->next;
       llpivot(head, smaller->next, larger, pivot);
    }
}
