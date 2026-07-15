#include "stdio.h"
#include "两数相加.h"
struct ListNode {
      int val;
      struct ListNode *next;
  };
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // 虚拟头节点
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* cur = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            cur->next = list1;
            list1 = list1->next;
        }
        else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }
    // 接上剩余部分
    cur->next = list1 ? list1 : list2;
    return dummy.next;
}

/*
* 递归写法
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
*/