#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

struct DoublyCircularLinkedList {
  struct Node *head;
  struct Node *tail;
  int size;
};

struct DoublyCircularLinkedList initList() {
  struct DoublyCircularLinkedList list = {NULL, NULL, 0};
  return list;
}

struct Node *createNode(int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

struct Node *insertFirst(struct DoublyCircularLinkedList *list, int value) {
  struct Node *newNode = createNode(value);
  if (list->head == NULL) {
    list->head = list->tail = newNode;
    newNode->next = newNode->prev = newNode;
  } else {
    newNode->next = list->head;
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->head->prev = newNode;
    list->head = newNode;
  }
  list->size++;
  return list->head;
}

struct Node *insertLast(struct DoublyCircularLinkedList *list, int value) {
  struct Node *newNode = createNode(value);
  if (list->head == NULL) {
    list->head = list->tail = newNode;
    newNode->next = newNode->prev = newNode;
  } else {
    newNode->prev = list->tail;
    newNode->next = list->head;
    list->tail->next = newNode;
    list->head->prev = newNode;
    list->tail = newNode;
  }
  list->size++;
  return list->head;
}

struct Node *insertAt(struct DoublyCircularLinkedList *list, int position,
                      int value) {
  if (position == 0) {
    return insertFirst(list, value);
  }

  struct Node *tempNode = list->head;
  int count = 0;
  while (count < position - 1 && tempNode->next != list->head) {
    tempNode = tempNode->next;
    count++;
  }

  if (position < 0 || position > list->size) {
    printf("Invalid position\n");
    return list->head;
  }

  struct Node *newNode = createNode(value);
  newNode->next = tempNode->next;
  newNode->prev = tempNode;
  tempNode->next->prev = newNode;
  tempNode->next = newNode;

  if (tempNode == list->tail) {
    list->tail = newNode;
  }
  list->size++;
  return list->head;
}

struct Node *deleteFirst(struct DoublyCircularLinkedList *list) {
  if (list->head == NULL)
    return NULL;
  struct Node *tempNode = list->head;
  if (list->head == list->tail) {
    printf("Deleted value : %d\n", tempNode->data);
    free(tempNode);
    list->head = list->tail = NULL;
    return NULL;
  }
  printf("Deleted value : %d\n", tempNode->data);
  list->head = list->head->next;
  list->tail->next = list->head;
  list->head->prev = list->tail;

  free(tempNode);
  list->size--;
  return list->head;
}

struct Node *deleteLast(struct DoublyCircularLinkedList *list) {
  if (list->head == NULL)
    return NULL;
  struct Node *tempNode = list->tail;
  if (list->head == list->tail) {
    printf("Deleted value : %d\n", tempNode->data);
    free(tempNode);
    list->head = list->tail = NULL;
    return NULL;
  }

  printf("Deleted value : %d\n", tempNode->data);
  list->tail = list->tail->prev;
  list->tail->next = list->head;
  list->head->prev = list->tail;
  free(tempNode);
  list->size--;
  return list->head;
}

struct Node *deleteAt(struct DoublyCircularLinkedList *list, int position) {
  if (list->head == NULL)
    return NULL;
  if (position == 0)
    return deleteFirst(list);

  struct Node *tempNode = list->head;
  int count = 0;
  while (count < position - 1 && tempNode->next != list->head) {
    tempNode = tempNode->next;
    count++;
  }

  if (position < 0 || position >= list->size) {
    printf("Invalid position\n");
    return list->head;
  }

  struct Node *toDelete = tempNode->next;
  printf("Deleted: %d\n", toDelete->data);

  tempNode->next = toDelete->next;
  toDelete->next->prev = tempNode;

  if (toDelete == list->tail)
    list->tail = tempNode;

  free(toDelete);
  list->size--;
  return list->head;
}

struct Node *deleteKey(struct DoublyCircularLinkedList *list, int deleteData) {
  if (list->head == NULL)
    return NULL;

  struct Node *tempNode = list->head;
  do {
    if (tempNode->data == deleteData) {
      if (tempNode == list->head && tempNode == list->tail) {
        printf("Deleted value: %d\n", tempNode->data);
        free(tempNode);
        list->head = list->tail = NULL;
        return NULL;
      } else if (tempNode == list->head)
        return deleteFirst(list);
      else if (tempNode == list->tail)
        return deleteLast(list);
      else {
        tempNode->prev->next = tempNode->next;
        tempNode->next->prev = tempNode->prev;
        printf("Deleted value: %d\n", tempNode->data);
        free(tempNode);
        list->size--;
        return list->head;
      }
    }
    tempNode = tempNode->next;
  } while (tempNode != list->head);

  printf("Node with given data: %d not found\n", deleteData);
  return list->head;
}

void traverseForward(struct DoublyCircularLinkedList *list) {
  if (list->head == NULL) {
    printf("Empty\n");
    return;
  }
  struct Node *tempNode = list->head;
  do {
    printf("%d <-> ", tempNode->data);
    tempNode = tempNode->next;
  } while (tempNode != list->head);
  printf("(back to head)\n");
}

void traverseBackward(struct DoublyCircularLinkedList *list) {
  if (list->head == NULL) {
    printf("Empty\n");
    return;
  }
  struct Node *tempNode = list->tail;
  do {
    printf("%d <-> ", tempNode->data);
    tempNode = tempNode->prev;
  } while (tempNode != list->tail);
  printf("(back to tail)\n");
}

bool isEmpty(struct DoublyCircularLinkedList *list) {
  return list->head == NULL;
}

struct Node *update(struct DoublyCircularLinkedList *list, int updateVal,
                    int newData) {
  struct Node *tempNode = search(list, updateVal);
  if (tempNode != NULL) {
    tempNode->data = newData;
    return tempNode;
  }
  return NULL;
}

struct Node *search(struct DoublyCircularLinkedList *list, int searchData) {
  if (list->head == NULL) {
    printf("Empty\n");
    return NULL;
  }
  int pos = 0;
  struct Node *tempNode = list->head;
  do {
    if (tempNode->data == searchData) {
      printf("Data %d found at position %d\n", tempNode->data, pos);
      return tempNode;
    }
    pos++;
    tempNode = tempNode->next;
  } while (tempNode != list->head);
  printf("Data %d not found\n", searchData);
  return NULL;
}

int size(struct DoublyCircularLinkedList *list) { return list->size; }

struct Node *reverse(struct DoublyCircularLinkedList *list) {
  if (list->head == NULL) {
    printf("Empty List\n");
    return NULL;
  }
  struct Node *current = list->head;
  struct Node *tempNode = NULL;
  do {
    tempNode = current->prev;
    current->prev = current->next;
    current->next = tempNode;
    current = current->prev;
  } while (current != list->head);
  tempNode = list->head;
  list->head = list->tail;
  list->tail = tempNode;

  return list->head;
}