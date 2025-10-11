#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *createNode(int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = NULL;
  return newNode;
}

struct Node *push(struct Node *head, int value) {
  struct Node *newNode = createNode(value);
  newNode->next = head;
  head = newNode;
  return head;
}

struct Node *pop(struct Node *head) {
  if (head == NULL)
    return NULL;
  if (head->next == NULL) {
    printf("Deleted value: %d\n", head->data);
    free(head);
    return NULL;
  }
  struct Node *tempNode = head;
  head = head->next;
  printf("Deleted value: %d\n", tempNode->data);
  free(tempNode);
  return head;
}
bool isEmpty(struct Node *head) { return head == NULL; }
int getSize(struct Node *head) {
  int count = 0;
  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}

int top(struct Node *head) {
  if (head == NULL) {
    printf("List empty\n");
    return -1;
  }
  return head->data;
}

void display(struct Node *head) {
  while (head != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}