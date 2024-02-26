#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

// Node & List Data Structures
typedef struct _node {
  char *_str;
  struct _node *_next;
  int index;
} Node;

typedef struct _StrList {
  Node *head;
  size_t size;
} StrList;

//--------------------------------------------
// Node implementation
//--------------------------------------------

Node *Node_alloc(const char *data, Node *next) {
  Node *p = (Node *)malloc(sizeof(Node)); // Allocation of memory space
  if (p==NULL) 
    {
        // Memory allocation failed
        return NULL;
    }
  p->_str = strdup(data); // Allocate memory for _str and copy data
  if (p->_str==NULL){
    free(p);
    return NULL; 
  }
   p->_next = next; // Link the new node
   p->index = (next != NULL) ? next->index + 1 : 0; // Set the index
   return p;
}

void Node_free(Node *node) { 
  if (node!=NULL)
  {
  free (node ->_str);
  free(node); 
  }
}
//--------------------------------------------
// List implementation
//--------------------------------------------

void StrList_free(StrList *StrList) {
  if (StrList == NULL)
    return;
  Node *current = StrList->head;
  while (current!=NULL) {
    Node *next = current ->_next;
    Node_free(current);
    current=next;
  }
  free(StrList);
}

StrList *StrList_alloc() {
  StrList *p = (StrList *)malloc(sizeof(StrList));
  p->head = NULL;
  p->size = 0;

  return p;
}

size_t StrList_size(const StrList *StrList)
 {
   return StrList->size;
 }

void StrList_insertLast(StrList *StrList, const char *data) {
  Node *curr = StrList->head; 
  Node *tmp = Node_alloc(data, curr);
  if (curr==NULL)
  {
    StrList->head = tmp;
  }
  else
  {
    // find the last node
    while (curr->_next != NULL)
     {
      curr = curr->_next;
     }
    curr->_next = tmp; // curr is the last node we found and add tmp after curr 
  }
   ++(StrList->size);
}

void StrList_insertAt(StrList *StrList, const char *data, int index) {
  if (index<0 || index > StrList -> size)
  {
    return;
  }
  Node *curr = StrList->head;
  for (int i = 0; i <= index - 1; i++) {
    curr = curr->_next;
  }
  // curr is the node before the index we want to add
  // curr->_next is the node after the index we want to add
  Node *after = curr->_next;

  Node *newNode = (Node *)malloc(sizeof(Node)); // Allocation of memory space
  newNode->_str = (char *)data;
  newNode->index = index;

  curr->_next = newNode;
  newNode->_next = after;
  StrList->size++; // newNode is in the list

  // update the indexes
  curr = after;
  while (curr->_next != NULL) {
    curr->index++;
    curr = curr->_next;
  }
}

char *StrList_firstData(const StrList *StrList) {
   return StrList->head->_str; }

void StrList_print(const StrList *StrList) {
  Node *p = StrList->head;
  while (p!=NULL) { 
    printf("%s", p->_str);
    p = p->_next;
  }
}

void StrList_printAt(const StrList *Strlist, int index) {
   if (index<0 || index >= Strlist->size)
  {
    return;
  }
  Node *p = Strlist->head;

  for (int i = 0; i < index && p!=NULL; i++) {
    p = p->_next;
  }
  printf("%s", p->_str);
}

int StrList_printLen(const StrList *Strlist) {
  int sum=0;
  Node *p = Strlist->head;

  while (p) {
    if (p->_str!=NULL)
    {
      sum += strlen(p->_str);
    }
    p = p->_next;
  }
  return sum;
}

int StrList_count(StrList *StrList, const char *data) {
  int counter=0;
  Node *p = StrList->head;

  while (p) {
    if (p->_str == data) {
      counter++;
    }
    p = p->_next;
  }
  return counter;
}

void StrList_removeAt(StrList *StrList, int index) {
  if (StrList==NULL || index<0 || index > StrList -> size)
    {
    return;
    }
    Node *p = StrList->head;
    Node *prev = NULL;
    
    for (int i=0; i<index; i++)
      {
      prev = p;
      p = p ->_next;
      }

    if (prev==NULL) // if perv is null, the node to be removed is the head
      {
        StrList->head = p->_next;
      } 
    else
      {
        prev->_next = p->_next;
      }
    // Update indices of subsequent nodes
    Node *tmp = p->_next;
    while (tmp != NULL) {
        tmp->index--;
        tmp = tmp->_next;
    }
    
    // Free memory of the node at index
    Node_free(p);
}
    
void StrList_remove(StrList *StrList, const char *data) {
    if (StrList == NULL)
        return;
    
    Node *current = StrList->head;
    Node *previous = NULL;
    
    while (current != NULL) {
        if (strcmp(current->_str, data) == 0) {
            Node *temp = current;
            if (previous == NULL) {
                StrList->head = current->_next;
            } else {
                previous->_next = current->_next;
            }
            current = current->_next;
            Node_free(temp);
            continue; // Skip index increment
        }
        previous = current;
        current = current->_next;
    }
    
    // Update indices of subsequent nodes
    current = StrList->head;
    int index = 0;
    while (current != NULL) {
        current->index = index++;
        current = current->_next;
    }
}

int StrList_isEqual(const StrList *StrList1, const StrList *StrList2) {
  const int eq = 0;
  const int neq = 1;

  const Node *p1 = StrList1->head;
  const Node *p2 = StrList2->head;

  while (p1 != NULL && p2 != NULL) {
    if (strcmp(p1->_str, p2->_str) != 0) {
      return neq;
    }
    p1 = p1->_next;
    p2 = p2->_next;
  }

  if (p1 != NULL || p2 != NULL) {
    return neq;
  }
  return eq;
}

StrList *StrList_clone(
    const StrList *originalList) {      // i changed the variable name to
                                        // originalList, bc Compilation problems
  StrList *cloneList = StrList_alloc(); // creat a list
  const Node *old = originalList->head;
  Node *copy = cloneList->head;

  cloneList->size = originalList->size;

  while (old) {
    copy->_next =
        Node_alloc(old->_str, copy); // the last Node address of clonelist is
                                     // the address copy is point to
    old = old->_next;
    copy = copy->_next;
  }

  return cloneList;
}

void StrList_reverse(StrList *StrList) {
  if (StrList==NULL)
  {
    return;
  }
  Node *p_curr = StrList->head;
  Node *p_prev = NULL;
  Node *p_next = NULL;

  while (p_curr) {
    p_next = p_curr->_next;
    p_curr->_next = p_prev;
    p_prev = p_curr;
    p_curr = p_next;
  }
  StrList->head = p_prev;
}
Node *merge(Node *list1, Node *list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    Node *result = NULL;

    if (strcmp(list1->_str, list2->_str) <= 0) {
        result = list1;
        result->_next = merge(list1->_next, list2);
    } else {
        result = list2;
        result->_next = merge(list1, list2->_next);
    }

    return result;
}

// help function for StrList_sort
Node *mergeSort(Node *head) {
  if (head == NULL) {
    return NULL; // Already sorted
  }
  
  if (head->_next == NULL) {
    return head;
  }

  // Find the middle of the list
  Node *slow = head;
  Node *fast = head->_next;
  while (fast != NULL && fast->_next != NULL) {
    slow = slow->_next;
    fast = fast->_next->_next;
  }

  // Split the list into two halves
  Node *secondHalf = slow->_next;
  slow->_next = NULL;

  // Recursively sort each half
  head = mergeSort(head);
  secondHalf = mergeSort(secondHalf);

  // Merge the sorted halves
  return merge(head, secondHalf);
}

// Function to sort a linked list of strings using merge sort
void StrList_sort(StrList *strList) {
  if (strList == NULL || strList->head == NULL || strList->size <= 1) {
    // Nothing to sort
    return;
  }

  // Perform merge sort
  strList->head = mergeSort(strList->head);
}

int StrList_isSorted(StrList *strList) {
  if (strList == NULL || strList->head == NULL || strList->size <= 1) {
    return 1; // An empty list or a list with one element is considered sorted
  }

  Node *current = strList->head;

  while (current->_next != NULL) {
    if (strcmp(current->_str, current->_next->_str) > 0) {
      return 0; // If the current string is greater than the next one, the list
                // is not sorted
    }
    current = current->_next;
  }

  return 1;
}