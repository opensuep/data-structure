#include <cstring>
#include <stdexcept>

using namespace std;

// 线性表
template <typename T>
class LinearList {
  public:
    size_t len;
    size_t capacity;
    T* data;

    LinearList() {
        this->len = 0;
        this->capacity = 16;
        this->data = new T(this->capacity);
    }

    LinearList(T* data, size_t size) {
        this->len = size;
        this->capacity = size * 2;
        this->data = new T[size];
        memcpy(this->data, data, size * sizeof(T));
    }

    ~LinearList() {
        delete this->data;
    }

    T operator[](size_t index) {
        if (index > this->len) {
            throw out_of_range("index out of range");
        } else {
            return this->data[index];
        }
    }

    void append(T value) {
        if (this->len + 1 > this->capacity) {
            this->capacity *= 2;
            T* ptr = new T[this->capacity];
            if (ptr == NULL) {
                throw bad_alloc();
            }
            memcpy(ptr, this->data, this->len * sizeof(T));
            delete this->data;
            this->data = ptr;
        }
        this->data[this->len++] = value;
    }

    void clear() {
        this->len = 0;
    }

    size_t index(T value) {
        for (size_t i = 0; i < this->len; ++i) {
            if (this->data[i] == value) {
                return i;
            }
        }
        throw "not in the list";
    }

    void insert(size_t index, T value) {
        if (index > this->len) {
            throw out_of_range("index out of range");
        }
        if (this->len + 1 > this->capacity) {
            this->capacity *= 2;
            T* ptr = new T[this->capacity];
            if (ptr == NULL) {
                throw bad_alloc();
            }
            memcpy(ptr, this->data, this->len * sizeof(T));
            delete this->data;
            this->data = ptr;
        }
        for (size_t i = this->len; i > index; --i) {
            this->data[i] = this->data[i - 1];
        }
        this->data[index] = value;
        ++this->len;
    }

    T pop(size_t index) {
        if (index > this->len) {
            throw out_of_range("index out of range");
        }
        T elem = this->data[index];
        for (size_t i = index; i < this->len - 1; ++i) {
            this->data[i] = this->data[i + 1];
        }
        --this->len;
        return elem;
    }

    T pop() {
        return this->pop(this->len - 1);
    }

    void remove(T value) {
        for (size_t i = 0; i < this->len; ++i) {
            if (this->data[i] == value) {
                this->pop(i);
                return;
            }
        }
        throw logic_error("not in the list");
    }

    void reverse() {
        for (size_t i = 0; i < this->len / 2; ++i) {
            swap(this->data[i], this->data[this->len - i - 1]);
        }
    }
};
