#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// 结构体定义

typedef struct {
    char isbn[14];
    char* name;
    int price;
} Book;

typedef struct {
    Book* data;
    size_t len;
    size_t capacity;
} List;

// 线性表操作

List* InitBookList() {
    List* list = new List;
    list->len = 0;
    list->capacity = 128;
    list->data = new Book[list->capacity];
    return list;
}

void DestroyBookList(List* list) {
    for (size_t i = 0; i < list->len; ++i) {
        delete list->data[i].name;
    }
    delete list->data;
    delete list;
}

void AppendBookList(List* list, Book* book) {
    if (list->len + 1 > list->capacity) {
        list->capacity *= 2;
        Book* ptr = new Book[list->capacity];
        memcpy(ptr, list->data, list->len * sizeof(Book));
        delete list->data;
        list->data = ptr;
    }
    memcpy(&list->data[list->len++], book, sizeof(Book));
}

// 图书操作

void AddBook(List* list) {
    char isbn[14];
    char* book_name = new char[1024];
    int price;
    cout << "ISBN: ";
    cin >> isbn;
    if (strlen(isbn) != 13) {
        cout << "ISBN 的长度必须为 13" << endl;
        return;
    }
    for (size_t i = 0; i < list->len; ++i) {
        if (strcmp(isbn, list->data[i].isbn) == 0) {
            cout << "ISBN 重复" << endl;
            return;
        }
    }
    cout << "书名: ";
    cin >> book_name;
    cout << "价格: ";
    cin >> price;
    if (price <= 0) {
        cout << "价格必须大于 0" << endl;
        return;
    }

    Book new_book;
    strcpy(new_book.isbn, isbn);
    new_book.name = book_name;
    new_book.price = price;
    AppendBookList(list, &new_book);
}

void PrintBookList(List* list) {
    for (size_t i = 0; i < list->len; ++i) {
        cout << i + 1 << ". " << list->data[i].isbn << " " << list->data[i].name
             << " " << list->data[i].price << endl;
    }
}

void Operation(List* list) {
    char* op = new char[64];
    while (1) {
        cout << ">>> ";
        cin >> op;
        if (strcmp(op, "add") == 0) {
            AddBook(list);
        } else if (strcmp(op, "show") == 0) {
            PrintBookList(list);
        } else if (strcmp(op, "exit") == 0) {
            delete[] op;
            break;
        } else {
            cout << "错误的命令" << endl;
        }
    }
}

int main(int argc, char** argv) {
    List* book_list = InitBookList();
    cout << "欢迎使用图书管理系统！" << endl;
    cout << "使用 \"add\" 添加图书; \"show\" 查看已经添加的图书; \"exit\" 退出"
         << endl;
    Operation(book_list);
    DestroyBookList(book_list);
    return 0;
}
