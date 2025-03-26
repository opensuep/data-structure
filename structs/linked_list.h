// 链表节点
template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

// 链表
template <typename T>
class LinkedList {
  public:
    Node<T>* head;

    LinkedList() {
        this->head = new Node<T>;
        this->head->next = nullptr;
    }

    ~LinkedList() {
        for (Node<T> node = this->head->next; node.next != nullptr;
             node = node.next) {
            delete node;
        }
    }
};
