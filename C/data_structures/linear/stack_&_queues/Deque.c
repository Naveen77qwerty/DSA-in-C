#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

struct Deque {
  struct Node *Front;
  struct Node *Rear;
  int size;
};

struct Deque initList() {
  struct Deque dq = {NULL, NULL, 0};
  return dq;
}

struct Node *createNode(int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

struct Node *insertFront(struct Deque *dq, int value) {
  struct Node *newNode = createNode(value);
  if (dq->Front == NULL)
    dq->Front = dq->Rear = newNode;
  else {
    newNode->next = dq->Front;
    dq->Front->prev = newNode;
    dq->Front = newNode;
  }
  dq->size++;
  return newNode;
}

struct Node *insertRear(struct Deque *dq, int value) {
  struct Node *newNode = createNode(value);
  if (dq->Front == NULL)
    dq->Front = dq->Rear = newNode;
  else {
    dq->Rear->next = newNode;
    newNode->prev = dq->Rear;
    dq->Rear = newNode;
  }
  dq->size++;
  return newNode;
}

struct Node *deleteFront(struct Deque *dq) {
  if (dq->Front == NULL) {
    printf("Deque is empty\n");
    return NULL;
  }

  struct Node *tempNode = dq->Front;
  dq->Front = dq->Front->next;

  if (dq->Front != NULL) {
    printf("Deleted value: %d\n", tempNode->data);
    dq->Front->prev = NULL;
  }
  free(tempNode);
  dq->size--;
  return dq->Front;
}

struct Node *deleteRear(struct Deque *dq) {
  if (dq->Front == NULL) {
    printf("Deque is empty\n");
    return NULL;
  }

  struct Node *tempNode = dq->Rear;
  dq->Rear = dq->Rear->prev;

  if (dq->Rear != NULL) {
    printf("Deleted value: %d\n", tempNode->data);
    dq->Rear->next = NULL;
  }
  free(tempNode);
  dq->size--;
  return dq->Rear;
}

void traverseForward(struct Deque *dq) {
  struct Node *tempNode = dq->Front;
  while (tempNode != NULL) {
    printf("%d <-> ", tempNode->data);
    tempNode = tempNode->next;
  }
  printf("NULL\n");
}

void traverseBackward(struct Deque *dq) {
  struct Node *tempNode = dq->Rear;
  while (tempNode != NULL) {
    printf("%d <-> ", tempNode->data);
    tempNode = tempNode->prev;
  }
  printf("NULL\n");
}

int getSize(struct Deque *dq) { return dq->size; }

int getfront(struct Deque *dq) {
  if (dq->Front == NULL) {
    printf("List empty\n");
    return;
  }
  return dq->Front->data;
}

int getRear(struct Deque *dq) {
  if (dq->Rear == NULL) {
    printf("List empty\n");
    return;
  }
  return dq->Rear->data;
}

bool isEmpty(struct Deque *dq) { return dq->Front == NULL; }