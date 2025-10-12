#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
  int data;
  struct TreeNode *left, *right;
} TreeNode;

typedef struct QNode {
  TreeNode *data;
  struct QNode *next;
} QNode;

typedef struct {
  QNode *head, *tail;
  int count;
} Queue;

void initQueue(Queue *q) {
  q->head = q->tail = NULL;
  q->count = 0;
}

bool isEmpty(Queue *q) { return q->count == 0; }

int getSize(Queue *q) { return q->count;}

void enqueue(Queue *q, TreeNode *node) {
  QNode *newNode = (QNode *)malloc(sizeof(QNode));
  newNode->data = node;
  newNode->next = NULL;
  if (q->count == 0) {
    q->head = q->tail = newNode;
  } else {
    q->tail->next = newNode;
    q->tail = newNode;
  }
  q->count++;
}

TreeNode *dequeue(Queue *q) {
  if (q->count == 0)
    return NULL;
  QNode *h = q->head;
  TreeNode *val = h->data;
  q->head = h->next;
  free(h);
  q->count--;
  if (q->count == 0)
    q->tail = NULL;
  return val;
}

TreeNode *newNode(int data) {
  TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

TreeNode *buildTree(int *arr, int n, int *idx) {
  (*idx)++;
  if (*idx >= n || arr[*idx] == -1)
    return NULL;
  TreeNode *node = newNode(arr[*idx]);
  node->left = buildTree(arr, n, idx);
  node->right = buildTree(arr, n, idx);
  return node;
}

void preOrder(TreeNode *r) {
  if (!r)
    return;
  printf("%d ", r->data);
  preOrder(r->left);
  preOrder(r->right);
}

void postOrder(TreeNode *r) {
  if (!r)
    return;
  postOrder(r->left);
  postOrder(r->right);
  printf("%d ", r->data);
}

void inOrder(TreeNode *r) {
  if (!r)
    return;
  inOrder(r->left);
  printf("%d ", r->data);
  inOrder(r->right);
}

void levelOrder(TreeNode *r) {
  if (!r) {
    printf("\n");
    return;
  }
  Queue q;
  q_init(&q);
  enqueue(&q, r);
  while (!isEmpty(&q)) {
    TreeNode *n = dequeue(&q);
    printf("%d ", n->data);
    if (n->left)
      enqueue(&q, n->left);
    if (n->right)
      enqueue(&q, n->right);
  }
  printf("\n");
}

int height(TreeNode *r) {
  if (!r)
    return 0;
  int lh = height(r->left), rh = height(r->right);
  return (lh > rh ? lh : rh) + 1;
}

int depth(TreeNode *r, int value) {
  if (!r)
    return -1;
  if (r->data == value)
    return 0;
  int left = depth(r->left, value);
  if (left != -1)
    return left + 1;
  int right = depth(r->right, value);
  if (right != -1)
    return right + 1;
  return -1;
}

TreeNode *findNode(TreeNode *r, int value) {
  if (!r)
    return NULL;
  if (r->data == value)
    return r;
  TreeNode *L = findNode(r->left, value);
  if (L)
    return L;
  return findNode(r->right, value);
}

int addChild(TreeNode *r, int parent, int child) {
  TreeNode *p = findNode(r, parent);
  if (!p)
    return 0;
  TreeNode *c = newNode(child);
  if (!p->left) {
    p->left = c;
    return 1;
  }
  if (!p->right) {
    p->right = c;
    return 1;
  }
  free(c);
  return 0;
}

int findHeightSubtree(TreeNode *r, int value) {
  TreeNode *n = findNode(r, value);
  return n ? height(n) : -1;
}

TreeNode *findCommonAncestor(TreeNode *r, int a, int b) {
  if (!r)
    return NULL;
  if (r->data == a || r->data == b)
    return r;
  TreeNode *L = findCommonAncestor(r->left, a, b);
  TreeNode *R = findCommonAncestor(r->right, a, b);
  if (L && R)
    return r;
  return L ? L : R;
}

int checkCompleteTree(TreeNode *r) {
  if (!r)
    return 0;
  Queue q;
  q_init(&q);
  enqueue(&q, r);
  int end = 0;
  while (!isEmpty(&q)) {
    TreeNode *n = dequeue(&q);
    if (n->left) {
      if (end)
        return 0;
      enqueue(&q, n->left);
    } else {
      end = 1;
    }
    if (n->right) {
      if (end)
        return 0;
      enqueue(&q, n->right);
    } else {
      end = 1;
    }
  }
  return 1;
}

TreeNode *deleteNode(TreeNode *root, int value) {
  if (!root)
    return NULL;
  if (!root->left && !root->right) {
    if (root->data == value) {
      free(root);
      return NULL;
    }
    return root;
  }

  Queue q;
  q_init(&q);
  enqueue(&q, root);

  TreeNode *nodeToDelete = NULL;
  TreeNode *last = NULL;
  TreeNode *parentOfLast = NULL;

  while (!isEmpty(&q)) {
    last = dequeue(&q);
    if (last->data == value)
      nodeToDelete = last;

    if (last->left) {
      parentOfLast = last;
      enqueue(&q, last->left);
    }
    if (last->right) {
      parentOfLast = last;
      enqueue(&q, last->right);
    }
  }

  if (!nodeToDelete) {
    printf("Value not found in tree\n");
    return root;
  }

  nodeToDelete->data = last->data;

  if (parentOfLast) {
    if (parentOfLast->left == last) {
      parentOfLast->left = NULL;
    } else if (parentOfLast->right == last) {
      parentOfLast->right = NULL;
    }
  }

  free(last);

  return root;
}