#include <iostream>
#include <queue>
#define MAX 1000
using namespace std;

typedef struct link
{
    int s = 1;
    int data;
    link *left;
    link *right;
} tree;

link *newNode(int value);
link *insertValue(tree *root, int value,
                  queue<link *> &q);
link *createTree(int arr[], int n);
void levelorder(tree *root);
void external(tree *root);
void SWAP(tree *a);
int distance(tree *node);
tree *merge(tree *h1, tree *h2);
tree *merge_node(tree *h1, tree *h2);
void zero(tree *root);
int ans[MAX], num = 0;

int main()
{
    int arr1[MAX], arr2[MAX];
    int node1, node2, total, element, end = 0;
    tree *root1 = (tree *)malloc(sizeof(tree));
    tree *root2 = (tree *)malloc(sizeof(tree));
    tree *root3 = (tree *)malloc(sizeof(tree));
    root1 = NULL;
    root2 = NULL;
    root3 = NULL;
    scanf("%d %d", &node1, &node2);
    total = 0;
    while (total < node1)
    {
        scanf("%d", &element);
        if (element == 0)
            node1++;
        arr1[total] = element;
        total++;
    }
    root1 = createTree(arr1, total);
    external(root1);
    total = 0;
    while (total < node2)
    {
        scanf("%d", &element);
        if (element == 0)
            node2++;
        arr2[total] = element;
        total++;
    }
    root2 = createTree(arr2, total);
    external(root2);
    root3 = merge_node(root1, root2);
    if (root3->left->s < root3->right->s)
        SWAP(root3);
    levelorder(root3);
    cout << root3->s + 1 << endl;
    external(root3);
    for (int i = num; i >= 0; i--)
    {
        if (ans[i] != 0 && ans[i] != -1)
        {
            end = i;
            break;
        }
    }
    for (int i = 0; i < end; i++)
        cout << ans[i] << " ";
    cout << ans[end] << endl;
    return 0;
}

link *newNode(int value)
{
    link *n = new link;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

link *insertValue(tree *root, int value, queue<link *> &q)
{
    link *node = newNode(value);
    if (root == NULL)
        root = node;
    else if (q.front()->left == NULL)
        q.front()->left = node;
    else if (q.front()->left != NULL)
    {
        q.front()->right = node;
        q.pop();
    }
    q.push(node);
    return root;
}

link *createTree(int arr[], int n)
{
    link *root = NULL;
    queue<link *> q;
    for (int i = 0; i < n; i++)
        root = insertValue(root, arr[i], q);
    return root;
}

void levelorder(tree *root)
{
    if (root == NULL)
        return;
    queue<link *> n;
    n.push(root);
    while (!n.empty())
    {
        ans[num] = n.front()->data;
        if (n.front()->left != NULL)
            n.push(n.front()->left);
        if (n.front()->right != NULL)
            n.push(n.front()->right);
        n.pop();
        num++;
    }
}

void SWAP(tree *node)
{
    tree *temp = node->left;
    node->left = node->right;
    node->right = temp;
}
int distance(tree *node)
{
    if (node == NULL)
        return -1;
    if (node->data == 0)
        return -1;
    return node->s;
}
tree *merge(tree *a, tree *b)
{
    if (a->left == NULL)
        a->left = b;
    else if (a->left->data == 0)
        a->left = b;
    else
    {
        a->right = merge_node(a->right, b);
        a->left->s = (distance(a->left->left) < distance(a->left->right)) ? 1 + distance(a->left->left) : 1 + distance(a->left->right);
        a->right->s = (distance(a->right->left) < distance(a->right->right)) ? 1 + distance(a->right->left) : 1 + distance(a->right->right);
        if (a->left->s < a->right->s)
            SWAP(a);
        a->s = 1 + distance(a->right);
    }
    return a;
}
tree *merge_node(tree *a, tree *b)
{

    if (a == NULL)
        return b;
    if (a->data == 0)
        return b;
    if (b == NULL)
        return a;
    if (b->data == 0)
        return a;
    if (a->data < b->data)
        return merge(a, b);
    else
        return merge(b, a);
}
void zero(tree *root)
{
    link *node = newNode(0);
    link *n = newNode(-1);
    root->left = node;
    root->right = node;
    root->left->left = n;
    root->left->right = n;
    root->right->left = n;
    root->right->right = n;
}
void external(tree *root)
{
    link *node = newNode(0);
    if (root->data == -1)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        root->left = node;
        zero(root->left);
        root->right = node;
        zero(root->right);
        return;
    }
    if (root->left == NULL)
    {
        root->left = node;
        zero(root->left);
        return;
    }
    external(root->left);
    if (root->right == NULL)
    {
        root->right = node;
        zero(root->right);
        return;
    }
    external(root->right);
}
