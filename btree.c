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
int BTreeCountNode(BTree t) {
    if (!t) {
        return 0;
    } else if (!t->lchild && !t->rchild) {
        return 1;
    }
    return BTreeCountNode(t->lchild) + BTreeCountNode(t->rchild);
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
    printf("Depth: %d\nNode: %d\n", BTreeDepth(tree), BTreeCountNode(tree));
    DestroyBTree(tree);
    return 0;
}
