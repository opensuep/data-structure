#include <stdio.h>
#include <stdlib.h>

typedef struct BNode {
    char data;
    struct BNode *lchild, *rchild;
} BNode, *BTree;

// 初始化二叉树
void CreateBTree(BTree* t) {
    char c = getchar();
    if (c == '.') {
        *t = NULL;
    } else {
        *t = (BTree)calloc(1, sizeof(BNode));
        (*t)->data = c;
        CreateBTree(&(*t)->lchild);
        CreateBTree(&(*t)->rchild);
    }
}

// 释放二叉树
void DestroyBTree(BTree t) {
    if (t) {
        DestroyBTree(t->lchild);
        DestroyBTree(t->rchild);
        free(t);
    }
}

// 中顺遍历二叉树
void BTreeInOrderTraverse(BTree t) {
    if (t) {
        BTreeInOrderTraverse(t->lchild);
        putchar(t->data);
        BTreeInOrderTraverse(t->rchild);
    }
}

// 后序遍历二叉树
void BTreePostOrderTraverse(BTree t) {
    if (t) {
        BTreePostOrderTraverse(t->lchild);
        BTreePostOrderTraverse(t->rchild);
        putchar(t->data);
    }
}

// 计算二叉树的深度
int BTreeDepth(BTree t) {
    if (!t) {
        return 0;
    } else {
        int m = BTreeDepth(t->lchild), n = BTreeDepth(t->rchild);
        return m > n ? m + 1 : n + 1;
    }
}

// 计算叶子节点的个数
int BTreeCountLeafNode(BTree t) {
    if (!t) {
        return 0;
    } else if (!t->lchild && !t->rchild) {
        return 1;
    } else {
        return BTreeCountLeafNode(t->lchild) + BTreeCountLeafNode(t->rchild);
    }
}

// 计算度为 1 的节点个数
int BTreeCountDegreeOneNode(BTree t) {
    if (!t) {
        return 0;
    } else if ((t->lchild && !t->rchild) || (!t->lchild && t->rchild)) {
        return 1 + BTreeCountDegreeOneNode(t->lchild) +
               BTreeCountDegreeOneNode(t->rchild);
    } else {
        return BTreeCountDegreeOneNode(t->lchild) +
               BTreeCountDegreeOneNode(t->rchild);
    }
}

// 计算度为 2 的节点个数
int BTreeCountDegreeTwoNode(BTree t) {
    if (!t) {
        return 0;
    } else if (t->lchild && t->rchild) {
        return 1 + BTreeCountDegreeTwoNode(t->lchild) +
               BTreeCountDegreeTwoNode(t->rchild);
    } else {
        return BTreeCountDegreeTwoNode(t->lchild) +
               BTreeCountDegreeTwoNode(t->rchild);
    }
}

int main(int argc, char** argv) {
    BTree tree = NULL;
    CreateBTree(&tree);
    printf("In-order: ");
    BTreeInOrderTraverse(tree);
    puts("");
    printf("Post-order: ");
    BTreePostOrderTraverse(tree);
    puts("");
    printf("Depth: %d\nLeaf node: %d\n", BTreeDepth(tree), BTreeCountLeafNode(tree));
    printf(
        "Degree: {1: %d, 2: %d}\n", BTreeCountDegreeOneNode(tree),
        BTreeCountDegreeTwoNode(tree)
    );
    DestroyBTree(tree);
    return 0;
}
