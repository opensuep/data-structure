#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define SUCCESS 1
#define ERROR -1

typedef struct {
    size_t len;
    size_t capacity;
    int* data;
} LinearList;

LinearList* InitList(int* data, size_t size) {
    LinearList* list = (LinearList*)calloc(1, sizeof(LinearList));
    if (data != NULL) {
        list->len = size;
        list->capacity = size * 2;
        list->data = (int*)calloc(size, sizeof(int));
        memcpy(list->data, data, size * sizeof(int));
    } else {
        list->len = 0;
        list->capacity = 16;
        list->data = (int*)calloc(list->capacity, sizeof(int));
    }
    return list;
}

void FreeList(LinearList* list) {
    free(list->data);
    free(list);
}

void ClearList(LinearList* list) { list->len = 0; }

int AppendList(LinearList* list, int value) {
    if (list->len + 1 > list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->len++] = value;
    return SUCCESS;
}

int GetListElement(LinearList* list, size_t n, int* value) {
    if (n < 0 || n > list->len) {
        return ERROR;
    } else {
        *value = list->data[n];
        return SUCCESS;
    }
}

size_t LocateListElement(LinearList* list, int value) {
    for (size_t i = 0; i < list->len; ++i) {
        if (list->data[i] == value) {
            return i + 1;
        }
    }
    return 0;
}

int InsertList(LinearList* list, size_t index, int value) {
    if (index < 0 || index > list->len) {
        return ERROR;
    }
    if (list->len + 1 > list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
    }
    for (size_t i = list->len; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    ++list->len;
    return SUCCESS;
}

int DeleteList(LinearList* list, size_t index) {
    if (index < 0 || index > list->len) {
        return ERROR;
    }
    for (size_t i = index; i < list->len - 1; ++i) {
        list->data[i] = list->data[i + 1];
    }
    --list->len;
    return SUCCESS;
}

int main(int argc, char* argv[]) {
    int data[5] = {0, 1, 2, 3, 4};
    LinearList* list = InitList(data, 5);
    cout << "The initial list: ";
    for (size_t i = 0; i < list->len; ++i) {
        cout << list->data[i] << " ";
    }
    cout << "\n";
    cout << "Append an element: ";
    AppendList(list, 5);
    for (size_t i = 0; i < list->len; ++i) {
        cout << list->data[i] << " ";
    }
    cout << "\n1 is at index " << LocateListElement(list, 1) << endl;
    cout << "Insert -1 at index 0: ";
    InsertList(list, 0, -1);
    for (size_t i = 0; i < list->len; ++i) {
        cout << list->data[i] << " ";
    }
    cout << "\nDelete index 2: ";
    DeleteList(list, 2);
    for (size_t i = 0; i < list->len; ++i) {
        cout << list->data[i] << " ";
    }
    cout << endl;
    FreeList(list);
    return 0;
}
