#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char isbn[14];
    char* name;
    float price;
} Book;

typedef struct {
    Book* data;
    size_t len;
    size_t capacity;
} List;

// 初始化线性表
List* InitList() {
    List* list = (List*)calloc(1, sizeof(List));
    list->len = 0;
    list->capacity = 128;
    list->data = (Book*)calloc(list->capacity, sizeof(Book));
    return list;
}

// 释放线性表
void DestroyList(List* list) {
    for (size_t i = 0; i < list->len; ++i) {
        free(list->data[i].name);
    }
    free(list->data);
    free(list);
}

// 在线性表末尾添加一项
void AppendBook(List* list, Book* book) {
    if (list->len + 1 > list->capacity) {
        list->capacity *= 2;
        Book* ptr = (Book*)calloc(list->capacity, sizeof(Book));
        memcpy(ptr, list->data, list->len * sizeof(Book));
        free(list->data);
        list->data = ptr;
    }
    memcpy(&list->data[list->len++], book, sizeof(Book));
}

// 添加一本书（包括数据合法性检查）
void AddBook(List* list) {
    Book book;
    book.name = (char*)calloc(1024, sizeof(char));
    printf("ISBN: ");
    scanf("%s", book.isbn);
    while (getchar() != '\n') {}
    if (strlen(book.isbn) != 13) {
        printf("ERROR: the length of ISBN should be 13\n");
        return;
    }
    for (size_t i = 0; i < list->len; ++i) {
        if (strcmp(book.isbn, list->data[i].isbn) == 0) {
            printf("ERROR: ISBN is existed\n");
            return;
        }
    }
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
    AppendBook(list, &book);
}

// 打印所有图书信息
void PrintBookList(List* list) {
    for (size_t i = 0; i < list->len; ++i) {
        printf(
            "%2zu. %s \"%s\" %.2f\n", i + 1, list->data[i].isbn,
            list->data[i].name, list->data[i].price
        );
    }
}

// 主循环
void CmdLoop(List* list) {
    char* op = (char*)calloc(64, sizeof(char));
    while (1) {
        printf(">>> ");
        scanf("%s", op);
        while (getchar() != '\n') {}
        if (strcmp(op, "add") == 0) {
            AddBook(list);
        } else if (strcmp(op, "ls") == 0) {
            PrintBookList(list);
        } else if (strcmp(op, "q") == 0) {
            free(op);
            break;
        } else {
            printf("ERROR: wrong command\n");
        }
    }
}

int main(int argc, char** argv) {
    printf("Welcome to use bookmgr!\n");
    printf(
        "Using \"add\" to add book; \"ls\" to list all books; \"q\" to exit\n"
    );
    List* book_list = InitList();
    CmdLoop(book_list);
    DestroyList(book_list);
    return 0;
}
