#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

// 初始化链栈
StackNode* InitStack() {
    return NULL;
}

// 释放链栈
void FreeStack(StackNode* stack) {
    while (stack != NULL) {
        StackNode* node = stack;
        stack = node->next;
        free(node);
    }
}

// 入栈
int PushStack(StackNode** stack, char bracket) {
    StackNode* node = (StackNode*)calloc(1, sizeof(StackNode));
    if (!node) {
        return 0;
    }
    node->data = bracket;
    node->next = *stack;
    *stack = node;
    return 1;
}

// 出栈
int PopStack(StackNode** stack, char* bracket) {
    if (!stack) {
        return 0;
    }
    if (bracket) {
        *bracket = (*stack)->data;
    }
    StackNode* node = *stack;
    *stack = (*stack)->next;
    free(node);
    return 1;
}

// 获取栈顶元素
char TopStack(StackNode* stack) {
    return stack->data;
}

// 栈是否为空
int StackEmpty(StackNode* stack) {
    return stack == NULL;
}

// 括号匹配
int Match() {
    StackNode* stack = InitStack();
    int flag = 1;
    char ch = getchar();
    while (ch != '\n' && flag) {
        switch (ch) {
            case '(':
            case '[':
                PushStack(&stack, ch);
                break;
            case ')':
                if (!StackEmpty(stack) && TopStack(stack) == '(') {
                    PopStack(&stack, NULL);
                } else {
                    flag = 0;
                }
                break;
            case ']':
                if (!StackEmpty(stack) && TopStack(stack) == '[') {
                    PopStack(&stack, NULL);
                } else {
                    flag = 0;
                }
                break;
        }
        ch = getchar();
    }
    if (StackEmpty(stack) && flag) {
        FreeStack(stack);
        return 1;
    } else {
        FreeStack(stack);
        return 0;
    }
}

int main(int argc, char** argv) {
    if (Match()) {
        puts("match");
    } else {
        puts("not match");
    }
    return 0;
}
