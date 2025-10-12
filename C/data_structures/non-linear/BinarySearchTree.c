#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct QNode {
  Node *data;
  struct QNode *next;
} QNode;

typedef struct Queue {
  QNode *front;
  QNode *rear;
} Queue;

Queue *createQueue() {
  Queue *q = (Queue *)malloc(sizeOf(Queue));
  q->front = q->rear = NULL;
  return q;
}

bool isEmpty(Queue *q) { return q->front == NULL; }

void enqueue(Queue *q, Node *data) {
  QNode *temp = (QNode *)malloc(sizeOf(QNode));
  temp->data = data;
  temp->next = NULL;
  if (q->rear == NULL) {
    q->front = q->rear = temp;
  } else {
    q->rear->next = temp;
    q->rear = temp;
  }
}

Node *dequeue(Queue *q) {
  if (isEmpty(q))
    return NULL;
  QNode *temp = q->front;
  Node *node = temp->data;
  q->front = q->front->next;
  if (q->front == NULL)
    q->rear = NULL;
  free(temp);
  return node;
}

Node *createNode(int data) {
  Node *n = (Node *)malloc(sizeOf(Node));
  n->data = data;
  n->left = n->right = NULL;
  return n;
}

Node *insert(Node *root, int data) {
  if (root == NULL)
    return createNode(data);
  if (data < root->data)
    root->left = insert(root->left, data);
  else if (data > root->data)
    root->right = insert(root->right, data);
  return root;
}

void inOrder(Node *root) {
  if (root != NULL) {
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
  }
}

void preOrder(Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void postOrder(Node *root) {
  if (root != NULL) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
  }
}

void levelOrder(Node *root) {
  if (root == NULL)
    return;
  Queue *q = createQueue();
  enqueue(q, root);
  while (!isEmpty(q)) {
    Node *node = dequeue(q);
    printf("%d ", node->data);
    if (node->left)
      enqueue(q, node->left);
    if (node->right)
      enqueue(q, node->right);
  }
  printf("\n");
}

Node *delete(Node *root, int key) {
  if (root == NULL)
    return root;
  if (key < root->data) {
    root->left = delete(root->left, key);
  } else if (key > root->data) {
    root->right = delete(root->right, key);
  } else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    } else if (root->right != NULL) {
      int succVal = successor(root);
      root->data = succVal;
      root->right = delete(root->right, succVal);
    } else {
      int predVal = predecessor(root);
      root->data = predVal;
      root->left = delete(root->left, predVal);
    }
  }
  return root;
}

int successor(Node *root) {
  root = root->right;
  while (root->left != NULL)
    root = root->left;
  return root->data;
}

int predecessor(Node *root) {
  root = root->left;
  while (root->right != NULL)
    root = root->right;
  return root->data;
}

int search(Node *root, int key) {
  if (root == NULL)
    return 0;
  if (root->data == key)
    return 1;
  else if (key < root->data)
    return search(root->left, key);
  else
    return search(root->right, key);
}

int findMin(Node *root) {
  if (root == NULL) {
    printf("Tree is empty\n");
    return -1;
  }
  while (root->left != NULL)
    root = root->left;
  return root->data;
}

int findMax(Node *root) {
  if (root == NULL) {
    printf("Tree is empty\n");
    return -1;
  }
  while (root->right != NULL)
    root = root->right;
  return root->data;
}

int height(Node *root) {
  if (root == NULL)
    return 0;
  int lh = height(root->left);
  int rh = height(root->right);
  return (lh > rh ? lh : rh) + 1;
}