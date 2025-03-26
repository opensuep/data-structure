#include "structs/linear_list.h"
#include <iostream>

template <typename T>
void print(LinearList<T>* list) {
    for (size_t i = 0; i < list->len; ++i) {
        cout << (*list)[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int data[5] = {0, 1, 2, 3, 4};
    LinearList<int> list = *new LinearList(data, 5);
    cout << "the initial list: ";
    print(&list);
    cout << "append an element: ";
    list.append(5);
    print(&list);
    cout << "list[" << list.index(1) << "] = 1" << endl;
    cout << "insert -1 at index 0: ";
    list.insert(0, -1);
    print(&list);
    cout << "delete index 6: ";
    list.pop(6);
    print(&list);
    cout << "swap it: ";
    list.reverse();
    print(&list);
    return 0;
}
