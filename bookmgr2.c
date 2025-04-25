#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char isbn[14];
    char* name;
    float price;
} Book;

typedef struct Node {
    Book book;
    struct Node* next;
} Node;

// 初始化链表
Node* InitList() {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->next = NULL;
    return node;
}

// 释放链表
void DestroyList(Node* head) {
    for (Node* node = head->next; node != NULL; node = node->next) {
        free(node->book.name);
        free(node);
    }
}

// 在链表头部添加一个节点
void AppendNode(Node* head, Book* book) {
    Node* new_node = (Node*)calloc(1, sizeof(Node));
    memcpy(&new_node->book, book, sizeof(Book));
    new_node->next = head->next;
    head->next = new_node;
}

// 删除一个特定的节点
void DeleteNode(Node* head, char* isbn) {
    if (head->next->next == NULL) {
        Node* node = head->next;
        if (strncmp(node->book.isbn, isbn, 13) == 0) {
            head->next = NULL;
            free(node->book.name);
            free(node);
            return;
        }
    }
    Node* prev = head;
    for (Node* now = head->next; now != NULL; now = now->next) {
        if (strncmp(now->book.isbn, isbn, 13) == 0) {
            prev->next = now->next;
            free(now->book.name);
            free(now);
            return;
        }
        prev = now;
    }
    printf("ERROR: book not found\n");
}

// 打印一个节点
void PrintNode(Node* node) {
    printf(
        "%s \"%s\" %.2f", node->book.isbn, node->book.name, node->book.price
    );
}

// 打印帮助
void PrintHelp() {
    printf("Show this help:  help\n");
    printf("Add a book:      add\n");
    printf("Delete a book:   del <isbn>\n");
    printf("Show all books:  ls\n");
    printf("Find a book:     find <name>\n");
    printf("Sort books:      sort [+|-][name|price]\n");
    printf("Exit system:     exit\n");
}

// 添加一本书（包括数据合法性检查）
void AddBook(Node* head) {
    Book book;
    book.name = (char*)calloc(1024, sizeof(char));
    printf("ISBN: ");
    scanf("%s", book.isbn);
    if (strlen(book.isbn) != 13) {
        printf("ERROR: the length of ISBN should be 13\n");
        return;
    }
    for (Node* now = head->next; now != NULL; now = now->next) {
        if (strncmp(book.isbn, now->book.isbn, 13) == 0) {
            printf("ERROR: ISBN is existed\n");
            free(book.name);
            return;
        }
    }
    while (getchar() != '\n') {}
    printf("Book name: ");
    fgets(book.name, 1024, stdin);
    book.name[strchr(book.name, '\n') - book.name] = '\0';
    printf("Price: ");
    scanf("%f", &book.price);
    while (getchar() != '\n') {}
    if (book.price <= 0) {
        printf("ERROR: price must be greater than 0\n");
        return;
    }
    AppendNode(head, &book);
}

// 打印所有图书信息
void PrintAllBook(Node* head) {
    size_t count = 1;
    for (Node* now = head->next; now != NULL; now = now->next) {
        printf("%2zu. ", count);
        PrintNode(now);
        puts("");
        ++count;
    }
}

// 寻找一本符合名称的书
void FindBook(Node* head, char* name) {
    size_t count = 0;
    for (Node* now = head->next; now != NULL; now = now->next) {
        if (strstr(now->book.name, name) != NULL) {
            ++count;
            printf("%2zu. ", count);
            PrintNode(now);
            puts("");
        }
    }
}

// 将书按照名称/价格排序
void SortBook(Node* head, char* cmd) {
    if (strlen(cmd) < 2) {
        printf("ERROR: command format error\n");
        return;
    }
    int coeff = 1, which = 0;
    if (cmd[0] == '+') {
        coeff = 1;
    } else if (cmd[0] == '-') {
        coeff = -1;
    } else {
        printf("ERROR: must be \"+\" or \"-\", found \"%c\"\n", cmd[0]);
        return;
    }
    if (strcmp(cmd + 1, "name") == 0) {
        which = 1;
    } else if (strcmp(cmd + 1, "price") == 0) {
        which = 2;
    } else {
        printf("ERROR: only can sort \"name\" or \"price\"\n");
        return;
    }

    if (head->next->next == NULL) {
        return;
    }
    int flag = 1;
    while (flag) {
        flag = 0;
        Node* prev = head->next;
        for (Node* now = prev->next; now != NULL; now = now->next) {
            int should_swap = 0;
            if (which == 1 &&
                strcmp(prev->book.name, now->book.name) * coeff > 0) {
                should_swap = 1;
            } else if (which == 2 &&
                       coeff * (prev->book.price - now->book.price) > 0) {
                should_swap = 1;
            }
            if (should_swap) {
                flag = 1;
                Book book;
                memcpy(&book, &prev->book, sizeof(Book));
                memcpy(&prev->book, &now->book, sizeof(Book));
                memcpy(&now->book, &book, sizeof(Book));
            }
            prev = now;
        }
    }
}

// 主循环
void CmdLoop(Node* head) {
    char* cmd = calloc(1024, sizeof(char));
    while (1) {
        printf(">>> ");
        char* ret = fgets(cmd, 1024, stdin);
        if (ret == NULL || feof(stdin) || ferror(stdin)) {
            free(cmd);
            return;
        }
        cmd[strchr(cmd, '\n') - cmd] = '\0';
        if (strlen(cmd) == 0) {
            continue;
        } else if (strcmp(cmd, "help") == 0) {
            PrintHelp();
        } else if (strcmp(cmd, "add") == 0) {
            AddBook(head);
        } else if (strncmp(cmd, "del ", 4) == 0) {
            DeleteNode(head, cmd + 4);
        } else if (strcmp(cmd, "ls") == 0) {
            PrintAllBook(head);
        } else if (strncmp(cmd, "find ", 5) == 0) {
            FindBook(head, cmd + 5);
        } else if (strncmp(cmd, "sort ", 5) == 0) {
            SortBook(head, cmd + 5);
        } else if (strcmp(cmd, "exit") == 0) {
            free(cmd);
            return;
        } else {
            printf("ERROR: command not found\n");
        }
    }
}

int main(int argc, char** argv) {
    printf("Welcome to use bookmgr!\n");
    printf("Type 'help' to see all commands.\n");
    Node* list = InitList();
    CmdLoop(list);
    DestroyList(list);
    return 0;
}
